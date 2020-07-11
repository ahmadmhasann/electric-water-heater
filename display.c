/*
 * File:   display.c
 * Author: Ahmed Hassan
 *
 * Created on July 8,  2020
 */


#define _XTAL_FREQ 8000000 
#include <xc.h>
#include "config.h"
#include "types.h"
#include "dio.h"
#include "ssd.h"
#include "counter.h"
#include "display.h"
#include "switch.h"

u8 settingModeFlag = 0;
u16 settingModeCounter = 0;
u8 blinkHeatingLedCounter = 0;
u8 deviceState;

void display_vid_init(void) {

    counter_vid_init();
    ssd_vid_init();
    switch_vid_init();

    /*turn off all port b leds*/
    dio_vid_set_pin_direction(B, 3, OUTPUT_PIN);
    dio_vid_set_pin_direction(B, 4, OUTPUT_PIN);
    dio_vid_set_pin_direction(B, 5, OUTPUT_PIN);
    dio_vid_set_pin_direction(B, 6, OUTPUT_PIN);
    dio_vid_set_pin_direction(B, 7, OUTPUT_PIN);
    dio_vid_set_pin_value(B, 3, LOW_PIN);
    dio_vid_set_pin_value(B, 4, LOW_PIN);
    dio_vid_set_pin_value(B, 5, LOW_PIN);
    dio_vid_set_pin_value(B, 6, LOW_PIN);
    dio_vid_set_pin_value(B, 7, LOW_PIN);
}

void display_vid_update(void) {

    deviceState = switch_u8_get_state();

    /*if device state is off, everything is off*/
    if (deviceState == DEVICE_OFF) {
        dio_vid_set_pin_value(B, HEATER_ELEMENT_LED, LOW_PIN);
        dio_vid_set_pin_value(B, DEVICE_ON_LED, LOW_PIN);
        ssd_vid_set_state(SSD_OFF);
        dio_vid_set_pin_value(HEATER_PORT_ENABLE, HEATER_PIN_ENABLE, LOW_PIN);
        dio_vid_set_pin_value(COOlER_PORT_ENABLE, COOlER_PIN_ENABLE, LOW_PIN);
    } else {
        dio_vid_set_pin_value(B, DEVICE_ON_LED, HIGH_PIN);
        /*Exit setting mode if 5 seconds passed without changing, the function is called every 20 ms, 250 calls = 5 seconds*/
        if (settingModeCounter == 250 && settingModeFlag == 1) {
            settingModeFlag = 0;
            settingModeCounter = 0;
        }
        if (settingModeFlag == DEVICE_SETTING_MODE_ON) {
            settingModeCounter++;
            /*Turn off cooling and heating elements in setting mode*/
            dio_vid_set_pin_value(HEATER_PORT_ENABLE, HEATER_PIN_ENABLE, LOW_PIN);
            dio_vid_set_pin_value(COOlER_PORT_ENABLE, COOlER_PIN_ENABLE, LOW_PIN);
            /*Turn off cooling and heating leds in setting mode*/
            /*blink ssd every 1 second*/
            if (settingModeCounter % 50 == 0) {
                if (ssd_u8_get_state() == SSD_ON)
                    ssd_vid_set_state(SSD_OFF);
                else
                    ssd_vid_set_state(SSD_ON);
            }
        }/*SSD doesn't blink if setting mode is off*/
        else {
            ssd_vid_set_state(SSD_ON);
            /*turning on cooling or heating element and led based on current state*/
            if (deviceState == HEATER_ON) {
                dio_vid_set_pin_value(HEATER_PORT_ENABLE, HEATER_PIN_ENABLE, HIGH_PIN);
                dio_vid_set_pin_value(COOlER_PORT_ENABLE, COOlER_PIN_ENABLE, LOW_PIN);
                /*blink heating element led every second*/
                blinkHeatingLedCounter++;
                if (blinkHeatingLedCounter % 50 == 0) {
                    blinkHeatingLedCounter = 0;
                    if (dio_u8_read_pin_value(B, HEATER_ELEMENT_LED) == HIGH_PIN)
                        dio_vid_set_pin_value(B, HEATER_ELEMENT_LED, LOW_PIN);
                    else
                        dio_vid_set_pin_value(B, HEATER_ELEMENT_LED, HIGH_PIN);
                }
            } else if (deviceState == COOLER_ON) {
                dio_vid_set_pin_value(HEATER_PORT_ENABLE, HEATER_PIN_ENABLE, LOW_PIN);
                dio_vid_set_pin_value(COOlER_PORT_ENABLE, COOlER_PIN_ENABLE, HIGH_PIN);
                blinkHeatingLedCounter = 0;
                dio_vid_set_pin_value(B, HEATER_ELEMENT_LED, HIGH_PIN);
            }
        }
        /*Update SSD symbol to last counter*/
        ssd_vid_set_symbol(counter_u8_get_counter());
    }

}

void display_vid_set_setting_mode_status(u8 mode) {
    settingModeFlag = mode;
    settingModeCounter = 0;
}

