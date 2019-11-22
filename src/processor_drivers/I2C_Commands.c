#include "I2C_Commands.h"
#include "driver_init.h"
#include "hal_i2c_m_os.h"
/*
	Configures I2C connection with standard settings and custom functions
*/
void configure_i2c_master(Sercom* sercom)
{
	// to prevent an error from compiling
	if (sercom) {
		;
	}
	return;
/* i2c_init should be called in driver_init.c, so don't need to do that */

}

/*
	Configure I2C with standard settings and standard functions
*/

void configure_i2c_standard(Sercom* sercom)
{
	// TODO: figure out what this did on equisat to make sure that default
	// settings are correct.

	// ALSO: figure out if we even need any of this stuff, it may be called in
	// the init functions that are already included

	// copied from asf-samd21>examples>driver_examples.c
	struct io_descriptor *I2C_0_io;

	i2c_m_os_get_io_descriptor(&I2C_0, &I2C_0_io);
	// TODO: figure out what the correct slave address is (and the length)
	int16_t slave_addr = 0; int32_t len = 0;
	// doesn't really matter because changes when read or write is called
	i2c_m_os_set_slaveaddr(&I2C_0, slave_addr, I2C_M_SEVEN);
	// default baudrate value is 400kHz (lowest). should change here if needed
	//i2c_m_os_set_baudrate(&I2C_0, 0, 100);
	i2c_m_os_enable(&I2C_0);
}

/*
	Sends a stop condition on the I2C bus
 */
void i2c_send_stop(void) {
    // not sure if we even need this function right now
	i2c_m_os_send_stop(&I2C_0);
}

/*
	Given the necessary arguments for i2c_m_sync_cmd_read, call that function
    on the main i2c instance

	*buffer - pointer to the buffer that we want to hold the information read
	length - the number of bytes that we want to read from the slave
*/
int32_t i2c_read_command(uint8_t *buffer, uint16_t len)
{
	// if we need more functionality, may need to use io_transfer function, but
 	// this is more simple right now
	// This will automatically send a stop signal, io_transfer does not do that
	return i2c_m_os_read(&I2C_0, buffer, len);
	//TODO error check (not sure if that should be here or in the driver)
}

/*
	Given a pointer to a packet, perform a write over I2C in standard fashion
*/
int32_t i2c_write_command(uint8_t *buffer, uint16_t len)
{
	// if we need more functionality, may need to use io_write function, but
 	// this is more simple right now
	i2c_m_os_write(&I2C_0, buffer, len);
}

/*
	Read data of length len into buffer buffer from address address on the i2c bus, using the corresponding stopping function
*/
int32_t readFromAddress(uint8_t* buffer, uint16_t len, int16_t address, bool should_stop){
	int32_t err;
	// need to do this everytime the address changes
	err = i2c_m_os_set_slaveaddr(&I2C_0, address, I2C_M_SEVEN);
	// if a non-zero value is returned, return error message
	if (err) {
		return err;
	}
	if(should_stop){
		return i2c_read_command(buffer, len);
	} else {
	// assuming that we will always stop
		return -1;
	}
}

/*
	Write data of length len to address address on the i2c bus
*/
int32_t writeDataToAddress(uint8_t* data, uint16_t len, int16_t address, bool should_stop){

	// assuming that we are using seven bit addresses
	i2c_m_os_set_slaveaddr(&I2C_0, address, I2C_M_SEVEN);
	 if(should_stop){
		return i2c_write_command(data, len);
 	} else {
		// need to figure out that damn io_transfer bs
	 	return -1;//return i2c_write_command_nostop(&write_packet);
	 }
}

/*
	Wrapper to write to a specific memory location (subAddress) at address
*/
int32_t writeDataToAddressSub(uint8_t* data, uint16_t len, int16_t address, uint8_t* subAddress, bool should_stop){
	int32_t err;
	err = writeDataToAddress(subAddress,1,address,should_stop);

	// error occurs if the value returned is not 0
	if (err){
		return code;
	}

	err = writeDataToAddress(data,len,address,should_stop);

	// whether there is an error or not, return code. will probably need to
	// with it when we write the driver 
	return err;
};

/*
	Read data of length len into buffer from address "address" at location memoryLocation on the i2c bus, using the corresponding stopping function
*/
int32_t readFromAddressAndMemoryLocation(uint8_t* buffer, uint16_t len, int16_t address, int16_t memoryLocation, bool should_stop){
	uint8_t data[] = {memoryLocation};

	// put the data at the address
	int32_t err = writeDataToAddress(data, 1, address, should_stop);
	// checks if a non-zero value was returned
	if (err) {
		return err;
	}
	return readFromAddress(buffer, len, address, 1);
}
