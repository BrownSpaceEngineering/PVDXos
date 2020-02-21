#include "MLX90614_IR_Sensor.h"

void MLX90614_init() {
	irPower(true);
}

/*
	Powers on or off the ir sensor.  True is on, false is off.
*/
// void irPower(bool trueIsOn){
//
//     // TODO: Figure out how to configure pins so that we can turn on sensor
// 	set_output(trueIsOn, P_IR_PWR_CMD);
// }

/*
	returns if the ir is powered on
*/
// bool isIROn(){
// 	return get_output(P_IR_PWR_CMD);
// }

// reads a 2 byte value which is sorted:
uint16_t MLX90614_read2ByteValue(uint16_t addr, uint16_t mem_addr, uint8_t* buf) {
	uint8_t read_buffer[2] = {0x0, 0x0};
	uint16_t sc = readFromAddressAndMemoryLocation(read_buffer,2,addr,mem_addr,1);
	*buf = read_buffer[0] | (((uint16_t)read_buffer[1]) << 8); // assumes LSB is in read_buffer[0]
	return sc;
}

// Function to read raw IR data from sensor. chan can be IR1 or IR2
uint16_t MLX90614_readRawIRData(uint16_t addr, IRChannel chan, uint8_t* buf) {
	return MLX90614_read2ByteValue(addr, (uint16_t)chan, buf);
}

// read ambient temperature
uint16_t MLX90614_read_amb(uint16_t addr, uint8_t* buf){
	uint16_t read_amb = MLX90614_read2ByteValue(addr, (uint16_t)AMBIENT, buf);
	return read_amb;
};

// average obj1 and obj2
uint16_t MLX90614_read_all_obj(uint16_t addr, uint8_t* buf){
	return MLX90614_read2ByteValue(addr, (uint16_t)OBJ1, buf);
}

// converts a data value from the sensor corresponding to a temperature memory address to a Celsius temperature
float dataToTemp(uint16_t data){
	float raw_temp = (float)data; // treat data as a 16-bit float
	return 0.02*raw_temp - 273.15;
}

// Read target temperature in degrees Celsius
// temp_target can be AMBIENT, OBJ1, OBJ2
uint16_t MLX90614_readTempC(uint16_t addr, IRTempTarget temp_target, float* buf) {
	return MLX90614_read2ByteValue(addr, (uint16_t) temp_target, (uint8_t*) buf);
}

// sanity check, should always return the same value as device_addr
uint16_t MLX90614_getAddress(uint16_t addr, uint8_t* rs) {
	return MLX90614_read2ByteValue(addr, MLX90614_SMBUS, rs);
}

// set the sensor to SLEEP mode (BROKEN)
uint16_t MLX90614_setSleepMode(uint16_t addr) {
	// enter SLEEP mode command = 1111_1111 (0xFF)
	// send PEC (Packet Error Code) (0xF3)
	uint8_t dataByte[2] = {(uint8_t)0xFF, (uint8_t)0xE8};
	// write to address with stop condition
	return writeDataToAddress(dataByte, 2, addr, 1);
}
