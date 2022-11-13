#include <atmel_start.h>
/** * Example task of using USART_0 to echo using the I/O abstraction. */
static void USART_0_example_task(void *p) {
    struct io_descriptor *io;
    uint16_t data;
    (void) p;
    usart_os_get_io(&USART_0, &io);
    for (;;) {
        if (io_read(io, (uint8_t *)&data, 2) == 2) {
            io_write(io, (uint8_t * ) & data, 2);
        }
    }
}

#define TASK_TRANSFER_STACK_SIZE (256/sizeof( portSTACK_TYPE )) \
#define TASK_TRANSFER_STACK_PRIORITY (tskIDLE_PRIORITY + 0)

static TaskHandle_t xCreatedTransferTask;
static void task_transfer_create(void) {
    if (xTaskCreate(USART_0_example_task,
                    "transfer",
                    TASK_TRANSFER_STACK_SIZE, NULL,
                    TASK_TRANSFER_STACK_PRIORITY,
                    &xCreatedTransferTask) != pdPASS) {
        while (1) { ; }
    }
}

static void tasks_run(void) { vTaskStartScheduler(); }

int main(void) {
    atmel_start_init();
    task_transfer_create();
    tasks_run();
    while (1) {}
}
