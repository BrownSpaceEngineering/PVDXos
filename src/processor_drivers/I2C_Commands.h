#ifndef I2C_COMMANDS_H
#define I2C_COMMANDS_H
#include "FreeRTOS.h"
#include "hal_i2c_m_os.h"

#define TIMEOUT 65535

// Initializing the global variable I2C_0
struct i2c_m_os_desc I2C_0;
// Initialize pointer to an IO io_descriptor
struct io_descriptor *IO;
// And mutex to keep things thread-safe
SemaphoreHandle_t i2c_mutex;

void i2c_init();

void i2c_send_stop(void);

int32_t writeDataToAddress(uint8_t* data, uint16_t len, uint16_t address, bool should_stop);
int32_t writeDataToAddressSub(uint8_t* data, uint16_t len, uint16_t address, uint8_t* subAddress, bool should_stop);
int32_t readFromAddressAndMemoryLocation(uint8_t* buffer, uint16_t len, uint16_t address, uint16_t memoryLocation, bool should_stop);
int32_t readFromAddress(uint8_t* buffer, uint16_t len, uint16_t address, bool should_stop);

#endif /* INCFILE1_H_ */
