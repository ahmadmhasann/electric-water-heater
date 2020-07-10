/*
 * File:   switch.c
 * Author: Ahmed Hassan
 *
 * Created on July 9, 2020
 */
#include <xc.h>
#include "types.h"
#include "adc.h"
#include "counter.h"
#include "dio.h"
#include "ssd.h"
#include "switch.h"
u8 current_state = DEVICE_ON;
u8 device_state = DEVICE_ON;
u16 avg_current_temperatuer = 0;
u8 readings_counter = 0;
u8 onOffButtonFlag = 0;

void switch_vid_init(void) {
    /*Output cooler and heater elements*/
    dio_vid_set_pin_direction(COOlER_PORT_ENABLE, COOlER_PIN_ENABLE, OUTPUT_PIN);
    dio_vid_set_pin_direction(HEATER_PORT_ENABLE, HEATER_PIN_ENABLE, OUTPUT_PIN);
    adc_vid_init();
    dio_vid_set_pin_direction(B, ON_OFF_BUTTON, INPUT_PIN);

}

void switch_vid_update(void) {

    if (dio_u8_read_pin_value(B, ON_OFF_BUTTON) == 0 && onOffButtonFlag == 0) {
        onOffButtonFlag = 1;
        if (device_state == DEVICE_OFF) {
            device_state = DEVICE_ON;
        } else if (device_state == DEVICE_ON) {
            device_state = DEVICE_OFF;
        }
    }
    if (dio_u8_read_pin_value(B, ON_OFF_BUTTON) != 0) {
        onOffButtonFlag = 0;
    }
    if (device_state == DEVICE_ON) {
        /*getting current temperature*/
        u8 current_temperature = adc_u8_get_value(2) * 0.488;
        readings_counter++;
        avg_current_temperatuer += current_temperature;

        /*Decide to turn on cooling on heating at the 10th read*/
        if (readings_counter == 10) {
            /*getting set temperature counter*/
            u8 set_temperature = counter_u8_get_counter();
            readings_counter = 0;
            avg_current_temperatuer /= 10;
            if (set_temperature > avg_current_temperatuer + 5) {
                current_state = HEATER_ON;
            }
            if (avg_current_temperatuer > set_temperature + 5) {
                current_state = COOLER_ON;
            }
            avg_current_temperatuer = 0;
        }


    }

}

u8 switch_u8_get_state(void) {
    if (device_state == DEVICE_ON)
        return current_state;
    else
        return device_state;
}