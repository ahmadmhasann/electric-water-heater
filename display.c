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
#include "macros.h"
#include "dio.h"
#include "ssd.h"
#include "counter.h"
#include "display.h"
u8 displayFlag = 0xff;
u8 settingModeFlag = 0;
u16 settingModeCounter = 0;

void display_vid_init(void) {
    counter_vid_init();
    
    ssd_vid_set_state(SSD_ON);
    ssd_vid_set_symbol(counter_u8_get_counter());
    dio_vid_set_port_value(B, LOW_PORT);
    
    ssd_vid_init();
    
    dio_vid_set_pin_direction(B, HEATER_ON_PIN, OUTPUT_PIN);
    dio_vid_set_pin_direction(B, COOLER_ON_PIN, OUTPUT_PIN);
    dio_vid_set_pin_direction(B, DEVICE_STATE_PIN, OUTPUT_PIN);
    dio_vid_set_pin_value(B, DEVICE_STATE_PIN, HIGH_PIN);
    
    
}

void display_vid_update(void) {
    /*Exit setting mode if 5 seconds passed without changing*/
    if (settingModeCounter == 250 && settingModeFlag == 1) {
        settingModeFlag = 0;
        settingModeCounter = 0;
    }

    /*Increment the counter and blink every second if setting mode is on*/
    if (settingModeFlag) {
        settingModeCounter++;
        if (settingModeCounter % 50 == 0) {
            if (ssd_u8_get_state() == SSD_ON)
                ssd_vid_set_state(SSD_OFF);
            else
                ssd_vid_set_state(SSD_ON);
        }
    }
    /*SSD doesn't blink if setting mode is off*/
    else {
        ssd_vid_set_state(SSD_ON);
    }
    
    /*Update SSD symbol to last counter*/
    ssd_vid_set_symbol(counter_u8_get_counter());
}

void display_set_setting_mode (u8 mode) {
    settingModeFlag = mode;
    settingModeCounter = 0;
}