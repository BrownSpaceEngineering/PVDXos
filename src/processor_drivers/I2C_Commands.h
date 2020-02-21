#ifndef I2C_COMMANDS_H
#define I2C_COMMANDS_H
#include "FreeRTOS.h"
#include "hal_i2c_m_os.h"

#include <atmel_start.h>


// // Do we need to include <atmel_start.h>? something is missing/weird for the
// // Program to change whenever the name of the main i2c_desc struct is changed
//
// //Start of stuff included from driver_init.h
// #include <hal_atomic.h>
// #include <hal_delay.h>
// #include <hal_gpio.h>
// #include <hal_init.h>
// #include <hal_io.h>
// #include <hal_sleep.h>
//
// #include <hal_adc_os.h>
//
// #include <hal_spi_m_os.h>
//
// #include <hal_i2c_m_os.h>
//
// #include <hal_usart_os.h>
//
// #include <hal_delay.h>
// #include <hal_pwm.h>
// #include <hpl_tc_base.h>
//
// #include <hal_wdt.h>
// //end of stuff included from driver.h
//
// //start of stuff included from driver.c
//
// #include <peripheral_clk_config.h>
// #include <utils.h>
// #include <hal_init.h>
// #include <hpl_gclk_base.h>
// #include <hpl_pm_base.h>
//
// //end of stuff included from driver.c


#define TIMEOUT 65535
#define I2C_ADDRESS 0x6E

// Initializing the global variable I2C_0
//extern struct i2c_m_os_desc I2C_0;
// Initialize pointer to an IO io_descriptor
struct io_descriptor *io_x;
// And mutex to keep things thread-safe
SemaphoreHandle_t i2c_mutex;

void i2c_init();

void i2c_send_stop(void);

int32_t writeDataToAddress(uint8_t* data, uint16_t len, uint16_t address, bool should_stop);
int32_t writeDataToAddressSub(uint8_t* data, uint16_t len, uint16_t address, uint8_t* subAddress, bool should_stop);
int32_t readFromAddressAndMemoryLocation(uint8_t* buffer, uint16_t len, uint16_t address, uint16_t memoryLocation, bool should_stop);
int32_t readFromAddress(uint8_t* buffer, uint16_t len, uint16_t address, bool should_stop);

#endif /* INCFILE1_H_ */
