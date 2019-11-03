#include <ADC_Interface.h>

typedef enum {
    // mux 0
    PDIODE_1_PIN = 0,
    PDIODE_2_PIN = 1,
    PDIODE_3_PIN = 2,
    PDIODE_4_PIN = 3,
    PDIODE_5_PIN = 4,
    PDIODE_6_PIN = 5,
    // _ = 6
    // _ = 7

    // mux 1
    // _ = 8
    // _ = 9
    // _ = 10
    // _ = 11
    // _ = 12
    // _ = 13
    // _ = 14
    // _ = 15

    // mux 2
    LIFEPO_1_PIN = 16,
    LIFEPO_2_PIN = 17,
    LION_1_PIN = 18,
    LION_2_PIN = 19,
    LED_1_PIN = 20,
    LED_2_PIN = 21,
    LED_3_PIN = 22,
    LED_4_PIN = 23,
} analog_sensor_pin;

// Translate to hardware addresses of LTC1380
uint8_t mux_number_to_address[4] = {
    0x90,
    0x92,
    0x94,
    0x96
};

void read_analog_signal(analog_sensor_pin pin, uint_16t* buf, uint8_t eloc, sig_id_t sig, bool priority, bool precise) {
    uint8_t pin_number = pin % 8;
    uint8_t mux_number = floor(pin/8);

    if (xSemaphoreTake(processor_adc_mutex, HARDWARE_MUTEX_WAIT_TIME_TICKS)) {
        uint8_t rs;
        uint16_t result;

        //Makes I2C call via gatekeeper
        status_code_genare_t sc = LTC1380_channel_select(mux_number_to_address[mux_number], pin_number, &rs);

        log_if_error(eloc, sc, priority);

        // switch built-in ADC mux and read
		commands_read_adc_mV(&result, mux_number, eloc, sig, priority, precise);

        xSemaphoreGive(processor_adc_mutex);
    } else {
        log_error(eloc, sig, priority);
		memset(buf, 0, sizeof(buf));
    }

    return 1;
}