/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example task of using ADC_0.
 */
void ADC_0_example_convert_task(void *p)
{
	(void)p;

	adc_os_enable_channel(&ADC_0, 0);

	while (1) {
		adc_os_start_conversion(&ADC_0);
		os_sleep(10);
	}
}

void ADC_0_example_read_task(void *p)
{
	uint8_t adc_values[8];
	uint8_t num = 0;

	(void)p;

	while (1) {
		num = adc_os_read_channel(&ADC_0, 0, adc_values, 8);
		if (num == 8) {
			/* read OK, handle data. */;
		} else {
			/* error. */;
		}
	}
}

/**
 * Example task of using I2C_0 to echo using the IO abstraction.
 * Assume the I2C device is AT30TSE temp sensor on IO1 Xplained Pro connected to
 * XPlained board EXT1.
 */
void I2C_0_example_task(void *p)
{
	struct io_descriptor *io;
	uint16_t              data;
	uint8_t               buf[2];

	(void)p;

	i2c_m_os_get_io(&I2C_0, &io);

	/* Address of the temp sensor. */
	i2c_m_os_set_slaveaddr(&I2C_0, 0x4f, 0);

	/* Set configuration to use 12-bit temperature */
	buf[0] = 1;
	buf[1] = 3 << 5;
	io_write(&I2C_0.io, buf, 2);
	/* Set to temperature register. */
	buf[0] = 0;
	io_write(&I2C_0.io, buf, 1);

	for (;;) {
		if (io->read(io, (uint8_t *)&data, 2) == 2) {
			/* read OK, handle data. */;
		} else {
			/* error. */;
		}
	}
}

/**
 * Example task of using SPI_0 to echo using the IO abstraction.
 */
void SPI_0_example_task(void *p)
{
	struct io_descriptor *io;
	uint16_t              data;

	(void)p;

	spi_m_os_get_io_descriptor(&SPI_0, &io);

	for (;;) {
		if (io->read(io, (uint8_t *)&data, 2) == 2) {
			/* read OK, handle data. */;
		} else {
			/* error. */;
		}
	}
}

/**
 * Example task of using USART_0 to echo using the IO abstraction.
 */
void USART_0_example_task(void *p)
{
	struct io_descriptor *io;
	uint16_t              data;

	(void)p;

	usart_os_get_io(&USART_0, &io);

	for (;;) {
		if (io->read(io, (uint8_t *)&data, 1) == 1) {
			io->write(io, (uint8_t *)&data, 1);
		}
	}
}

void delay_example(void)
{
	delay_ms(5000);
}

/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_set_parameters(&PWM_0, 10000, 5000);
	pwm_enable(&PWM_0);
}

/**
 * Example of using WDT_0.
 */
void WDT_0_example(void)
{
	uint32_t clk_rate;
	uint16_t timeout_period;

	clk_rate       = 1000;
	timeout_period = 4096;
	wdt_set_timeout_period(&WDT_0, clk_rate, timeout_period);
	wdt_enable(&WDT_0);
}
