#include "I2C_Commands.h"
// #include "driver_init.h"

/*
	Configure I2C with standard settings and standard functions
*/

void i2c_init() {
	// ALSO: figure out if we even need any of this stuff, it may be called in
	// the init functions that are already included

	// creating a mutex so that we know all i2c calls are threadsafe
	i2c_mutex = xSemaphoreCreateMutex();
	if (i2c_mutex == NULL) { //making sure mutex was created
		return;
	}
	// copied from asf-samd21>examples>driver_examples.c

	i2c_m_os_get_io(&I2C_0, &IO);
	// TODO: figure out what the correct slave address is (and the length)
	// int16_t slave_addr = 0; int32_t len = 0;
	// // doesn't really matter because changes when read or write is called
	// i2c_m_os_set_slaveaddr(&I2C_0, slave_addr, I2C_M_SEVEN);
	// default baudrate value is 400kHz (lowest). should change here if needed
	//i2c_m_os_set_baudrate(&I2C_0, 0, 100);
}

/*
	Sends a stop condition on the I2C bus
 */
void i2c_send_stop_unsafe(void) {
    /* not sure if we even need this function right now */
	// lokcing the mutex (waitiing indefinitely until we get it)
	i2c_m_os_send_stop(&I2C_0);
}

/*
	Given the necessary arguments for i2c_m_sync_cmd_read, call that function
    on the main i2c instance

	*buffer - pointer to the buffer that we want to hold the information read
	length - the number of bytes that we want to read from the slave
*/
int32_t i2c_read_command_unsafe(uint8_t *buffer, uint16_t len) {
	// if we need more functionality, may need to use io_transfer function, but
 	// this is more simple right now

	// This will automatically send a stop signal, io_transfer does not do that

	// NOTE: I am not sure what the correct first argument is for this
	// ALSO: This should not be considered a "function definition" it is declared
	// 		in the hal_i2c_m_os.h file
	return io_read(IO, buffer, len);
	//TODO error check (not sure if that should be here or in the driver)

}

/*
	Given a pointer to a packet, perform a write over I2C in standard fashion
*/
int32_t i2c_write_command_unsafe(uint8_t *buffer, uint16_t len) {
	// if we need more functionality, may need to use io_transfer (or io_write)?
	// function, but this is more simple right now

	// locking the mutex
	// This will automatically send a stop signal, io_transfer does not do that

	//use debug port
	// use the io_read and io_write()
	return io_write(IO, buffer, len);
	//TODO error check (not sure if that should be here or in the driver)
}

/*
 * Should ony be called within a funtion that uses a mutex
 */
int32_t i2c_set_slave_address_unsafe(int16_t address) {

	return i2c_m_os_set_slaveaddr(&I2C_0, address, I2C_M_SEVEN);
}

/*
	Read data of length len into buffer buffer from address address on the i2c bus, using the corresponding stopping function
*/
int32_t readFromAddress(uint8_t* buffer, uint16_t len, uint16_t address, bool should_stop){
	int32_t err;
	xSemaphoreTake(i2c_mutex, portMAX_DELAY);
	// need to do this everytime the address changes
	err = i2c_set_slave_address_unsafe(address);
	// if a non-zero value is returned, return error message
	if (err) {
		xSemaphoreGive(i2c_mutex);
		return err;
	}
	if(should_stop){
		int32_t ret = i2c_read_command_unsafe(buffer, len);
		xSemaphoreGive(i2c_mutex);
		return ret;
	} else {
	// assuming that we will always stop
		xSemaphoreGive(i2c_mutex);
		return (int32_t) -1;
	}
}

/*
	Write data of length len to address address on the i2c bus
	Do this without locking the mutex so that we can call this in a different
	funtion that locks the mutex.
*/
int32_t writeDataToAddressUnsafe(uint8_t* data, uint16_t len, uint16_t address, bool should_stop){

	// assuming that we are using seven bit addresses
	i2c_set_slave_address_unsafe(address);
	int32_t ret;
	 if(should_stop){
		ret = i2c_write_command_unsafe(data, len);
 	} else {
		// need to figure out that damn io_transfer bs
	 	ret = -1;//return i2c_write_command_nostop(&write_packet);
	 }
	return ret;
}

/*
	Write data of length len to address address on the i2c bus
*/
int32_t writeDataToAddress(uint8_t* data, uint16_t len, uint16_t address, bool should_stop){

	xSemaphoreTake(i2c_mutex, portMAX_DELAY);
	// assuming that we are using seven bit addresses
	i2c_set_slave_address_unsafe(address);
	int32_t ret;
	 if(should_stop){
		ret = i2c_write_command_unsafe(data, len);
 	} else {
		// need to figure out that damn io_transfer bs
	 	ret = -1;//return i2c_write_command_nostop(&write_packet);
	 }
	xSemaphoreGive(i2c_mutex);
	return ret;
}

/*
	Wrapper to write to a specific memory location (subAddress) at address
*/
int32_t writeDataToAddressSub(uint8_t* data, uint16_t len, uint16_t address, uint8_t* subAddress, bool should_stop){
	int32_t err;

	xSemaphoreTake(i2c_mutex, portMAX_DELAY);
	err = writeDataToAddressUnsafe(subAddress, 1, address, should_stop);

	// error occurs if the value returned is not 0
	if (err){
		xSemaphoreGive(i2c_mutex);
		return err;
	}

	err = writeDataToAddressUnsafe(data, len, address, should_stop);

	// whether there is an error or not, return code. will probably need to
	// with it when we write the driver
	xSemaphoreGive(i2c_mutex);
	return err;
};

/*
	Read data of length len into buffer from address "address" at location memoryLocation on the i2c bus, using the corresponding stopping function
*/
int32_t readFromAddressAndMemoryLocation(uint8_t* buffer, uint16_t len, uint16_t address, uint16_t memoryLocation, bool should_stop){
	uint8_t data[] = {memoryLocation};

	xSemaphoreTake(i2c_mutex, portMAX_DELAY);
	// put the data at the address
	int32_t err = writeDataToAddress(data, 1, address, should_stop);
	// checks if a non-zero value was returned
	if (err) {
		xSemaphoreGive(i2c_mutex);
		return err;
	}
	err = readFromAddress(buffer, len, address, 1);
	xSemaphoreGive(i2c_mutex);
	return err;
}
