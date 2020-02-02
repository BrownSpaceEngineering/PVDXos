#ifndef _MLX90614_IR_SENSOR_H_
#define _MLX90614_IR_SENSOR_H_

//#include "../config/proc_pins.h"
#include "../processor_drivers/I2C_Commands.h"
// #include "../processor_drivers/Direct_Pin_Commands.h"

#define MLX90614_SHOULD_STOP false

#define MLX90614_WHOAMI	0x2e

//ram addresses
#define MLX90614_RAWIR1 0x04
#define MLX90614_RAWIR2 0x05
#define MLX90614_TA 0x06
#define MLX90614_TOBJ1 0x07
#define MLX90614_TOBJ2 0x08

//eeprom addresses
#define MLX90614_SMBUS 0x2E

/* Might not use enums */
// typedef enum {DEFAULT = MLX90614_DEFAULT_I2CADDR,
//               TBOARD_IR2 = MLX90614_TBOARD_IR2
//               } uint16_t;

typedef enum {IR1 = MLX90614_RAWIR1,
             IR2 = MLX90614_RAWIR2} IRChannel;

typedef enum {AMBIENT = MLX90614_TA,
              OBJ1 = MLX90614_TOBJ1,
              OBJ2 = MLX90614_TOBJ2} IRTempTarget;

void MLX90614_init(void);
uint16_t MLX90614_read_all_obj(uint16_t addr, uint8_t* buf);
uint16_t MLX90614_read_amb(uint16_t addr, uint8_t* buf);
uint16_t MLX90614_read2ByteValue(uint16_t addr, uint16_t mem_addr, uint8_t* buf);
uint16_t MLX90614_readRawIRData(uint16_t addr, IRChannel chan, uint8_t* buf);
float dataToTemp(uint16_t data);
uint16_t MLX90614_readTempC(uint16_t addr, IRTempTarget temp_target, float* buf);

uint16_t MLX90614_getAddress(uint16_t addr, uint8_t* rs);

uint16_t MLX90614_setSleepMode(uint16_t addr);

void irPower(bool trueIsOn);
bool isIROn(void);

#endif
