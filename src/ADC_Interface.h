/*
 * IncFile1.h
 *
 * Created: 5/8/2015 3:20:25 PM
 *  Author: Daniel
 */


#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

void read_analog_signal(analog_sensor_pin pin, uint_16t* buf, uint8_t eloc, sig_id_t sig, bool priority, bool precise);

#endif 
