#include "atmel_start.h"

#include "./watchdog.h"
#include "samd21a/include/component/wdt.h"

int main(void) {
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    __enable_irq();
    watchdog_init(WDT_CONFIG_PER_16K, true);

    /* Set pin PB30 to output */
    REG_PORT_DIR1 |= (1 << 30);
    // REG_PORT_OUT1 |= (1 << 30);

    /* Replace the code below with your application code */
    // FREERTOS_V1000_0_example();

    REG_PORT_OUT1 &= ~(1 << 30); // Turn on light
    delay_ms(100);
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
