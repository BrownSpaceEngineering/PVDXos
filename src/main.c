#include <atmel_start.h>
#include "processor_drivers/I2C_Commands.h"
#include "sensor_drivers/MLX90614_IR_Sensor.h"

// TODO: maybe consider making this bigger
#define TASK_EXAMPLE_STACK_SIZE (512 / sizeof(portSTACK_TYPE))
#define TASK_EXAMPLE_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedExampleTask;

//NOTE: I2C Pins: SCL - PA09, SDA - PA08


/**
 * OS example task
 *
 * \param[in] p The void pointer for OS task Standard model.
 *
 */
static void test_task(void *p)
{
	(void)p;
	while (1) {
		uint8_t buf[2];
		//checkAddress();
		//atmel_i2c_example(0);
		// For some reason this did not enter the dummy handler when I stepped through
		// it in gdb
		// Did not use the scope to see what happened in the write, but it did return
		i2c_commands_init();
		MLX90614_read_amb(0x7A, buf);
		float temp = dataToTemp(buf);
		os_sleep(500);
	}
}


void atmel_i2c_example(void *p)
{
	struct io_descriptor *io;
	uint16_t              data;
	uint8_t               buf[2];

	(void)p;

	i2c_m_os_get_io(&I2C_0, &io);

	/* Address of the temp sensor. */
	// i2c_m_os_set_slaveaddr(&I2C_0, 0x4f, 0);

	// change the address to the same one that we use
	i2c_m_os_set_slaveaddr(&I2C_0, 0x28, 0);

	/* Set configuration to use 12-bit temperature */
	buf[0] = 1;
	buf[1] = 3 << 5;
	// for some reason this doesnt segfault, but it still returns an error
	io_write(&I2C_0.io, buf, 2);
	/* Set to temperature register. */
	buf[0] = 0;
	io_write(&I2C_0.io, buf, 1);

	// for (;;) {
	// 	if (io->read(io, (uint8_t *)&data, 2) == 2) {
	// 		/* read OK, handle data. */;
	// 	} else {
	// 		/* error. */;
	// 	}
	// }
}

void checkAddress() {
	int32_t add = 0;

	struct io_descriptor *io;
	uint16_t              data;
	uint8_t               buf[2];

	i2c_m_os_get_io(&I2C_0, &io);

	/* Address of the temp sensor. */
	// i2c_m_os_set_slaveaddr(&I2C_0, 0x4f, 0);

	/* Set configuration to use 12-bit temperature */
	buf[0] = 1;
	buf[1] = 3 << 5;
	// for some reason this doesnt segfault, but it still returns an error

	int32_t ret;
	while (add < 129) {
		// change the address to the same one that we use
		i2c_m_os_set_slaveaddr(&I2C_0, add, 0);
		ret = io_write(&I2C_0.io, buf, 2);
		if ((ret < 10) && (ret > 0) ) {
			it_works(add);
		}
		add++;
	}
}
void it_works(int32_t addr) {
	int i = addr;
	return;
}

/*
 * Example
 */
void FREERTOS_V1000_0_example2(void)
{

	if (xTaskCreate(
	        test_task, "Example", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedExampleTask)
	    != pdPASS) {
		while (1) {
			;
		}
	}

	vTaskStartScheduler();

	return;
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	// Initializing i2c
	//i2c_init();



	/* Replace the code below with your application code */
	// FREERTOS_V1000_0_example();
  FREERTOS_V1000_0_example2();

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
