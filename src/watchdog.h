#pragma once
#include "atmel_start.h"
#include "globals.h"
#include "portable.h"
#include "samd21a/include/component/wdt.h"

#define WATCHDOG_MS_DELAY 1000

// Initializes the memory for all the watchdog lists (i.e. for tasks to check in)
// and starts the watchdog timer.
void watchdog_init(int watchdog_period, bool always_on);

void watchdog_early_warning_callback();

// Returns 0 on success and -1 on failure
void watchdog_pet(void);

// Returns 0 on success and -1 on failure
void watchdog_kick(void);

// Returns 0 on success and -1 on failure
int watchdog_check_in(task_type_t task_index);

int register_task(task_type_t task_index);

int unregister_task(task_type_t task_index);

void watchdog_as_function(void);