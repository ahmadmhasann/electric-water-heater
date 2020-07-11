/*
 * File:   counter.c
 * Author: Ahmed Hassan
 *
 * Created on July 8,  2020
 */


#define _XTAL_FREQ 8000000 
#include <xc.h>
#include "types.h"
#include "dio.h"
#include "eeprom_external.h"
#include "display.h"
#include "counter.h"
u8 buttonPressedFlag = 0;
u8 counter = 60;
void counter_vid_init(void) {
    /*UP/DOWN buttons are inputs*/
    dio_vid_set_pin_direction(B, UP_BUTTON, INPUT_PIN);
    dio_vid_set_pin_direction(B, DOWN_BUTTON, INPUT_PIN);
    
    /*getting last set temperature from eeprom*/
    counter = eeprom_external_vid_read(0);
    if (counter < 35 || counter > 75 || counter % 5 != 0)
        counter = 60;
}

void counter_vid_update(void) {
    if (dio_u8_read_pin_value(B, UP_BUTTON) == 0 && buttonPressedFlag == 0) {
        display_vid_set_setting_mode_status(DEVICE_SETTING_MODE_ON);
        buttonPressedFlag = 1;
        if (counter + 5 < 80) {
            eeprom_external_vid_write(0, counter + 5);
            counter += 5;
        }
    } 
    else if (dio_u8_read_pin_value(B, DOWN_BUTTON) == 0 && buttonPressedFlag == 0) {
        display_vid_set_setting_mode_status(DEVICE_SETTING_MODE_ON);
        buttonPressedFlag = 1;
        if (counter - 5 > 30) {
            eeprom_external_vid_write(0, counter - 5);
            counter -= 5;
        }
    }
    if (dio_u8_read_pin_value(B, UP_BUTTON) && dio_u8_read_pin_value(B, DOWN_BUTTON))
        buttonPressedFlag = 0;
}


u8 counter_u8_get_counter (void) {
    return counter;
}