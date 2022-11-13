#include <atmel_start.h>

#define TASK_EXAMPLE_STACK_SIZE (128 / sizeof(portSTACK_TYPE))
#define TASK_EXAMPLE_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
static TaskHandle_t      xCreatedOnTask;
static TaskHandle_t      xCreatedOffTask;
static SemaphoreHandle_t disp_mutex;

struct io_descriptor *io;


// TODO: try using the semaphore to negotiate between a task that turns the
// light on and one that turns it off

// TODO: try the RTOS-optimized USART lib
static void light_task(void *p)
{
    (void)p;
    while (1) {
//        if (xSemaphoreTake(disp_mutex, ~0)) {
            REG_PORT_OUT1 &= ~(1<<30);
            os_sleep(100);
            REG_PORT_OUT1 |= (1<<30);
            os_sleep(100);
            REG_PORT_OUT1 &= ~(1<<30);
            os_sleep(100);
            REG_PORT_OUT1 |= (1<<30);
            os_sleep(100);
            REG_PORT_OUT1 &= ~(1<<30);
//            xSemaphoreGive(disp_mutex);
//        }
        os_sleep(750);
    }
}

static uint8_t example_str[2] = "01";

static void usart_task(void *p)
{
    (void)p;
    while (1) {
//        if (xSemaphoreTake(disp_mutex, ~0)) {
            io_write(io, example_str, 2);
//            xSemaphoreGive(disp_mutex);
//        }
        os_sleep(750);
    }
}

static void usart_task2(void *p)
{
    (void)p;
    char *newmsg = "PVDX";
    while (1) {
//        if (xSemaphoreTake(disp_mutex, ~0)) {
            io_write(io, (uint8_t *) newmsg, 4);
//            xSemaphoreGive(disp_mutex);
//        }
        os_sleep(750);
    }
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

    disp_mutex = xSemaphoreCreateMutex();
//
//    if (disp_mutex == NULL) {
//        REG_PORT_OUT1 &= ~(1<<30);
//        delay_ms(100);
//        REG_PORT_OUT1 |= (1<<30);
//        delay_ms(100);
//        REG_PORT_OUT1 &= ~(1<<30);
//        delay_ms(100);
//        REG_PORT_OUT1 |= (1<<30);
//        delay_ms(100);
//        REG_PORT_OUT1 &= ~(1<<30);
//        delay_ms(100);
//        REG_PORT_OUT1 |= (1<<30);
//        delay_ms(1000);
//    }

    // TODO: why does setting the baud rate break things?
//    usart_sync_set_baud_rate(&USART_0, 9600);

    usart_sync_set_parity(&USART_0, USART_PARITY_NONE);
    usart_sync_set_character_size(&USART_0, USART_CHARACTER_SIZE_8BITS);
    usart_sync_set_stopbits(&USART_0, USART_STOP_BITS_ONE);
    usart_sync_get_io_descriptor(&USART_0, &io);
    usart_sync_enable(&USART_0);

//    usart_os_set_mode(&USART_0, USART_MODE_ASYNCHRONOUS);

//    usart_os_set_parity(&USART_0, USART_PARITY_NONE);
//    usart_os_set_baud_rate(&USART_0, 9600);
//    usart_os_set_data_order(&USART_0, USART_DATA_ORDER_LSB);
//    usart_os_set_character_size(&USART_0, USART_CHARACTER_SIZE_8BITS);
//    usart_os_set_stopbits(&USART_0, USART_STOP_BITS_ONE);
//    usart_os_get_io(&USART_0, &io);

//    usart_sync_get_io_descriptor(&USART_0, &io);
//    usart_sync_enable(&USART_0);
    // Testing code to verify USART is working (it is!)

    /* Set pin PB30 to output */
	REG_PORT_DIR1 |= (1<<30);


//	/* Replace the code below with your application code */
//	FREERTOS_V1000_0_example();


    if (xTaskCreate(
            light_task, "Light", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedOnTask)
        != pdPASS) {
        // ERROR!
    }

//    if (xTaskCreate(
//            usart_task, "USART", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedOnTask)
//        != pdPASS) {
//        // ERROR!
//    }

    if (xTaskCreate(
            usart_task2, "USART2", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedOnTask)
        != pdPASS) {
        // ERROR!
    }

//    if (xTaskCreate(
//            off_task, "Off", TASK_EXAMPLE_STACK_SIZE, NULL, TASK_EXAMPLE_STACK_PRIORITY, xCreatedOffTask)
//        != pdPASS) {
//        while (1) {
//            REG_PORT_OUT1 &= ~(1<<30);
//            delay_ms(100);
//            REG_PORT_OUT1 |= (1<<30);
//            delay_ms(100);
//            REG_PORT_OUT1 &= ~(1<<30);
//            delay_ms(100);
//            REG_PORT_OUT1 |= (1<<30);
//            delay_ms(100);
//            REG_PORT_OUT1 &= ~(1<<30);
//            delay_ms(100);
//            REG_PORT_OUT1 |= (1<<30);
//            delay_ms(1000);
//        }
//    }
    vTaskStartScheduler();
    while (1) { }

//	/* Make it blink! */
//	while (1) {
//		REG_PORT_OUT1 &= ~(1<<30);
//		delay_ms(100);
//		REG_PORT_OUT1 |= (1<<30);
//		delay_ms(100);
//		REG_PORT_OUT1 &= ~(1<<30);
//		delay_ms(100);
//		REG_PORT_OUT1 |= (1<<30);
//		delay_ms(100);
//		REG_PORT_OUT1 &= ~(1<<30);
//		delay_ms(100);
//		REG_PORT_OUT1 |= (1<<30);
//		delay_ms(1000);
//	}
}