#ifndef I2C_COMMANDS_H
#define I2C_COMMANDS_H


#define TIMEOUT 65535

// Initializing the global variable I2C_0
struct i2c_m_os_desc I2C_0;


void configure_i2c_master(Sercom* sercom);
void configure_i2c_standard(Sercom* sercom);

void i2c_send_stop(void);


int32_t i2c_read_command(struct i2c_master_packet* packet_address);
int32_t i2c_read_command_nostop(struct i2c_master_packet* packet_address);
int32_t i2c_write_command(struct i2c_master_packet* packet_address);
int32_t i2c_write_command_nostop(struct i2c_master_packet* packet_address);

int32_t writeDataToAddress(uint8_t* data, uint8_t len, uint8_t address, bool should_stop);
int32_t writeDataToAddressSub(uint8_t* data, uint8_t len, uint8_t address, uint8_t* subAddress, bool should_stop);
int32_t readFromAddressAndMemoryLocation(uint8_t* buffer, uint8_t len, uint8_t address, uint8_t memoryLocation, bool should_stop);
int32_t readFromAddress(uint8_t* buffer, uint8_t len, uint8_t address, bool should_stop);

#endif /* INCFILE1_H_ */
