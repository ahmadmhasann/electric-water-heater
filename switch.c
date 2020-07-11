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
#include "display.h"
u8 current_state = DEVICE_ON;
u16 avg_current_temperature = 0;
u8 readings_counter = 0;
u8 onOffButtonFlag = 0;

void switch_vid_init(void) {
    /*Output cooler and heater elements*/
    dio_vid_set_pin_direction(COOlER_PORT_ENABLE, COOlER_PIN_ENABLE, OUTPUT_PIN);
    dio_vid_set_pin_direction(HEATER_PORT_ENABLE, HEATER_PIN_ENABLE, OUTPUT_PIN);
    adc_vid_init();
    /*on/off button is input*/
    dio_vid_set_pin_direction(B, ON_OFF_BUTTON, INPUT_PIN);
}

void switch_vid_update(void) {
    /*check if on/off buttons pressed*/
    if (dio_u8_read_pin_value(B, ON_OFF_BUTTON) == 0 && onOffButtonFlag == 0) {
        onOffButtonFlag = 1;
        if (current_state != DEVICE_OFF) {
            current_state = DEVICE_OFF;
            display_vid_set_setting_mode_status(DEVICE_SETTING_MODE_OFF);
        } else {
            current_state = DEVICE_ON;
        }
    }
    if (dio_u8_read_pin_value(B, ON_OFF_BUTTON) != 0) {
        onOffButtonFlag = 0;
    }
    if (current_state != DEVICE_OFF) {
        /*getting current temperature*/
        u8 current_temperature = adc_u8_get_value(2) * 0.488;
        readings_counter++;
        avg_current_temperature += current_temperature;
        /*Decide to turn on cooling on heating at the 10th read*/
        if (readings_counter == 10) {
            /*getting set temperature counter*/
            u8 set_temperature = counter_u8_get_counter();
            readings_counter = 0;
            avg_current_temperature /= 10;
            if (set_temperature > avg_current_temperature + 5) {
                current_state = HEATER_ON;
            }
            if (avg_current_temperature > set_temperature + 5) {
                current_state = COOLER_ON;
            }
            if (current_state != HEATER_ON && current_state != COOLER_ON)
                current_state = avg_current_temperature > set_temperature ? COOLER_ON : HEATER_ON;
            avg_current_temperature = 0;
        }
    }
}

u8 switch_u8_get_state(void) {
    return current_state;
}