#include "atmel_start.h"

#include "samd21a/include/component/wdt.h"

void pet_watchdog(Wdt *watchdog) {
    // Feed the watchdog (reset the watchdog counter)
    watchdog->CLEAR.reg = WDT_CLEAR_CLEAR_KEY;

    // Wait for synchronization
    while (watchdog->STATUS.bit.SYNCBUSY)
        ;
}

void delay_100ms_with_watchdog(Wdt *watchdog) {
    pet_watchdog(watchdog);
    for (int i = 0; i < 100; i++) {
        delay_ms(1);
        pet_watchdog(watchdog);
    }
    pet_watchdog(watchdog);
}

int main(void) {
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();

    Wdt *pWDT = WDT; // Create a pointer to the WDT instance.

    // Disable the watchdog before configuring
    pWDT->CTRL.reg &= ~(WDT_CTRL_ENABLE | WDT_CTRL_WEN);

    // Wait for synchronization
    while (pWDT->STATUS.bit.SYNCBUSY)
        ;

    // Configure the watchdog
    pWDT->CONFIG.reg = WDT_CONFIG_PER_16K | 0; // Set the window value (e.g., no windowing)

    // Wait for synchronization
    while (pWDT->STATUS.bit.SYNCBUSY)
        ;

    // Enable the watchdog
    pWDT->CTRL.reg |= WDT_CTRL_ENABLE;

    // Wait for synchronization
    while (pWDT->STATUS.bit.SYNCBUSY)
        ;

    /* Set pin PB30 to output */
    REG_PORT_DIR1 |= (1 << 30);
    // REG_PORT_OUT1 |= (1 << 30);
    REG_PORT_OUT1 &= ~(1 << 30);

    /* Replace the code below with your application code */
    // FREERTOS_V1000_0_example();

    /* Make it blink! */
    // while (1) {
    //     REG_PORT_OUT1 &= ~(1 << 30);
    //     delay_100ms_with_watchdog(pWDT);
    //     REG_PORT_OUT1 |= (1 << 30);
    //     delay_100ms_with_watchdog(pWDT);
    //     REG_PORT_OUT1 &= ~(1 << 30);
    //     delay_100ms_with_watchdog(pWDT);
    //     REG_PORT_OUT1 |= (1 << 30);
    //     delay_100ms_with_watchdog(pWDT);
    //     REG_PORT_OUT1 &= ~(1 << 30);
    //     delay_100ms_with_watchdog(pWDT);
    //     REG_PORT_OUT1 |= (1 << 30);
    //     delay_100ms_with_watchdog(pWDT);
    // }
}
