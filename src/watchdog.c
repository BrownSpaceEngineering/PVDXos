/*
This file:
1. Watchdog Initialization code
*/

#include "watchdog.h"

static volatile Wdt *watchdog = WDT;
static uint32_t running_times[NUM_TASKS];
static bool should_checkin[NUM_TASKS];
static bool watchdog_is_enabled = false;

// If the difference between the current time and the time in the running_times array is greater than the allowed time,
// then the task has not checked in and the watchdog should reset the system.
static uint32_t allowed_times[NUM_TASKS] = {1000, 1000, 1000};

void watchdog_init(int watchdog_period, bool always_on) {

    // Initialize the running times
    for (int i = 0; i < NUM_TASKS; i++) {
        running_times[i] = 0;
        // 0 Is a special value that indicates that the task has not checked in yet (or is not running)
    }
    for (int i = 0; i < NUM_TASKS; i++) {
        should_checkin[i] = false;
    }
    // Make sure that critical tasks are always supposed to check in
    should_checkin[WATCHDOG_TASK] = true;

    // Disable the watchdog before configuring
    WDT->CTRL.reg &= ~(WDT_CTRL_ENABLE | WDT_CTRL_WEN);
    while (WDT->STATUS.bit.SYNCBUSY)
        ;

    // Configure the watchdog
    uint8_t watchdog_earlywarning_period = watchdog_period - 1;
    // Early warning will trigger halfway through the watchdog period
    WDT->EWCTRL.bit.EWOFFSET = watchdog_earlywarning_period;

    WDT->CONFIG.reg = watchdog_period | watchdog_earlywarning_period; // Set the window value (e.g., no windowing)

    // Enable early warning interrupt
    WDT->INTENSET.bit.EW = 1;

    while (WDT->STATUS.bit.SYNCBUSY)
        ;

    // Enable the watchdog
    if (always_on) {
        WDT->CTRL.reg |= WDT_CTRL_ENABLE;
    } else {
        WDT->CTRL.reg |= WDT_CTRL_ENABLE | WDT_CTRL_ALWAYSON;
    }
    while (WDT->STATUS.bit.SYNCBUSY)
        ;

    watchdog_is_enabled = true;

    NVIC_SetPriority(WDT_IRQn, 3); // Set the interrupt priority
    NVIC_EnableIRQ(WDT_IRQn);      // Enable the WDT_IRQn interrupt
    NVIC_SetVector(WDT_IRQn, (uint32_t)(&WDT_Handler));
}

void WDT_Handler(void) {
    // Check if the early warning interrupt is triggered
    if (WDT->INTFLAG.bit.EW) {
        // Clear the early warning interrupt flag
        WDT->INTFLAG.reg = 1;
        // Call the early warning callback function
        watchdog_early_warning_callback();
    }
}

void watchdog_early_warning_callback() {
    // This function gets called when the watchdog is almost out of time
    // TODO Test if this works
    // This is also fine to leave blank
    REG_PORT_OUT1 |= (1 << 30); // Turn off light
    delay_ms(100);
    REG_PORT_OUT1 &= ~(1 << 30);
    delay_ms(100);
    REG_PORT_OUT1 |= (1 << 30);
    delay_ms(100);
    REG_PORT_OUT1 &= ~(1 << 30);
    delay_ms(100);
    REG_PORT_OUT1 |= (1 << 30);
    delay_ms(100);
    REG_PORT_OUT1 &= ~(1 << 30);
}

void watchdog_pet() {
    watchdog->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;

    // Wait for synchronization
    while (watchdog->STATUS.bit.SYNCBUSY)
        ;
}

// If I am a battery task, I call this function: `watchdog_check_in(BATTERY_TASK)`
int watchdog_checkin(task_type_t task_index) {
    // Guards
    if (task_index >= NUM_TASKS) {
        return -1;
    }
    if (!should_checkin[task_index]) {
        return -1;
    }
    uint32_t current_time = xTaskGetTickCount();
    running_times[(unsigned int)task_index] = current_time;
    return 0;
}

void watchdog_kick() {
    watchdog->CLEAR.reg = 0x12; // Wrong value for clear key, so it kicks the watchdog
    // This function should never return, since it writes the wrong clear key and causes a system reset
}

// The task passed as an argument should now be running and therefore we should expect it to checkin
int register_task(task_type_t task_index) {
    if (task_index >= NUM_TASKS || task_index < 0) {
        return -1;
    }
    if (should_checkin[(unsigned int)task_index] == true) {
        // Something has gone wrong, we define that unregistered tasks must always set their slot to 0
        // TODO add some logging here or something idk
        watchdog_kick();
    }
    running_times[(unsigned int)task_index] = xTaskGetTickCount();
    should_checkin[(unsigned int)task_index] = 1;
    return 0;
}

// This should be called when a task is intentionally disabled, and we should not be expecting it to checkin.
int unregister_task(task_type_t task_index) {
    if (task_index >= NUM_TASKS || task_index < 0) {
        return -1;
    }
    if (should_checkin[(unsigned int)task_index] == false) {
        // Shouldn't be unregistering if it's already unregsitered
        // TODO add some logging here or something idk
        watchdog_kick();
    }
    running_times[(unsigned int)task_index] = 0xDEADBEEF;
    should_checkin[(unsigned int)task_index] = 0;
    return 0;
}

// Functions above are basically helpers that other tasks will use
// This function is the actual watchdog itself
void watchdog_as_function() {
    // Iterate through the running times and check if any tasks have not checked in within the allowed time
    uint32_t current_time = xTaskGetTickCount();
    for (int i = 0; i < NUM_TASKS; i++) {
        if (should_checkin[i]) {
            uint32_t process_last_checkin_time = running_times[i];
            uint32_t time_difference = current_time - process_last_checkin_time;
            // If there is overflow, then current_time will be less than last_checkin_time
            // This actually doesn't matter and we can just do the math as normal
            if (time_difference > allowed_times[i]) {
                // The task has not checked in within the allowed time, so we should reset the system
                watchdog_kick();
            }
        }
    }
    // If we get to the bottom of the loop, all tasks must have been fine, so pet the watchdog
    watchdog_pet();
    watchdog_checkin(WATCHDOG_TASK);
    vTaskDelay(WATCHDOG_MS_DELAY);
}