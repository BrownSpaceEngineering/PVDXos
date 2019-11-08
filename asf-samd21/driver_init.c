/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

/* The channel amount for ADC */
#define ADC_0_CH_AMOUNT 1

/* The buffer size for ADC */
#define ADC_0_BUFFER_SIZE 16

/* The maximal channel number of enabled channels */
#define ADC_0_CH_MAX 0

struct adc_os_descriptor         ADC_0;
struct adc_os_channel_descriptor ADC_0_ch[ADC_0_CH_AMOUNT];

static uint8_t ADC_0_buffer[ADC_0_BUFFER_SIZE];
static uint8_t ADC_0_map[ADC_0_CH_MAX + 1];

struct i2c_m_os_desc I2C_0;

struct spi_m_os_descriptor SPI_0;

struct usart_os_descriptor USART_0;
uint8_t                    USART_0_buffer[USART_0_BUFFER_SIZE];

struct pwm_descriptor PWM_0;

struct wdt_descriptor WDT_0;

/**
 * \brief ADC initialization function
 *
 * Enables ADC peripheral, clocks and initializes ADC driver
 */
static void ADC_0_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, ADC);
	_gclk_enable_channel(ADC_GCLK_ID, CONF_GCLK_ADC_SRC);
	adc_os_init(&ADC_0, ADC, ADC_0_map, ADC_0_CH_MAX, ADC_0_CH_AMOUNT, &ADC_0_ch[0]);
	adc_os_register_channel_buffer(&ADC_0, 0, ADC_0_buffer, ADC_0_BUFFER_SIZE);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA02, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA02, PINMUX_PA02B_ADC_AIN0);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA03, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA03, PINMUX_PA03B_ADC_AIN1);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PB08, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PB08, PINMUX_PB08B_ADC_AIN2);
}

void I2C_0_PORT_init(void)
{

	gpio_set_pin_pull_mode(PA08,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA08, PINMUX_PA08C_SERCOM0_PAD0);

	gpio_set_pin_pull_mode(PA09,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA09, PINMUX_PA09C_SERCOM0_PAD1);
}

void I2C_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM0);
	_gclk_enable_channel(SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC);
	_gclk_enable_channel(SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC);
}

void I2C_0_init(void)
{
	I2C_0_CLOCK_init();
	i2c_m_os_init(&I2C_0, SERCOM0);
	i2c_m_os_enable(&I2C_0);
	I2C_0_PORT_init();
}

void SPI_0_PORT_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(PA16, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA16,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA16, PINMUX_PA16C_SERCOM1_PAD0);

	gpio_set_pin_level(PA18,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PA18, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PA18, PINMUX_PA18C_SERCOM1_PAD2);

	gpio_set_pin_level(PA19,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PA19, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PA19, PINMUX_PA19C_SERCOM1_PAD3);
}

void SPI_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM1);
	_gclk_enable_channel(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
}

void SPI_0_init(void)
{
	SPI_0_CLOCK_init();
	spi_m_os_init(&SPI_0, SERCOM1);
	spi_m_os_enable(&SPI_0);
	SPI_0_PORT_init();
}

void USART_0_PORT_init(void)
{

	gpio_set_pin_function(PA12, PINMUX_PA12C_SERCOM2_PAD0);

	gpio_set_pin_function(PA13, PINMUX_PA13C_SERCOM2_PAD1);
}

void USART_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM2);
	_gclk_enable_channel(SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC);
}

void USART_0_init(void)
{

	USART_0_CLOCK_init();
	usart_os_init(&USART_0, SERCOM2, USART_0_buffer, USART_0_BUFFER_SIZE, (void *)NULL);
	usart_os_enable(&USART_0);
	USART_0_PORT_init();
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(PB01, PINMUX_PB01E_TC7_WO1);
}

void PWM_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, TC7);
	_gclk_enable_channel(TC7_GCLK_ID, CONF_GCLK_TC7_SRC);
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, TC7, _tc_get_pwm());
}

void WDT_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBA, WDT);
	_gclk_enable_channel(WDT_GCLK_ID, CONF_GCLK_WDT_SRC);
}

void WDT_0_init(void)
{
	WDT_0_CLOCK_init();
	wdt_init(&WDT_0, WDT);
}

void system_init(void)
{
	init_mcu();

	ADC_0_init();

	I2C_0_init();

	SPI_0_init();

	USART_0_init();

	delay_driver_init();

	PWM_0_init();

	WDT_0_init();
}
