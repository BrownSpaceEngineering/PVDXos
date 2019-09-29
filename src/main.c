#include <atmel_start.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace the code below with your application code */

	/* Set pin PB30 to output */
	REG_PORT_DIR1 |= (1<<30);

	/* Make it blink! */
	while (1) {
		REG_PORT_OUT1 &= ~(1<<30);
		delay_ms(100);
		REG_PORT_OUT1 |= (1<<30);
		delay_ms(100);
		REG_PORT_OUT1 &= ~(1<<30);
		delay_ms(100);
		REG_PORT_OUT1 |= (1<<30);
		delay_ms(100);
		REG_PORT_OUT1 &= ~(1<<30);
		delay_ms(100);
		REG_PORT_OUT1 |= (1<<30);
		delay_ms(1000);
	}
}
