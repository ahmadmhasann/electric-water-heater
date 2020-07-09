/*
 * File:   ssd.c
 * Author: Hassan
 *
 * Created on July 6,  2020
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


u16 ssdSymbol = 0;
u8 ssdState = SSD_ON;


void ssd_vid_init(void) {
    dio_vid_set_port_direction(SSD_PORT, 0);
    dio_vid_set_pin_direction(SSD_ENABLE_1_PORT, SSD_ENABLE_1_PIN, 0);
    dio_vid_set_pin_direction(SSD_ENABLE_2_PORT, SSD_ENABLE_2_PIN, 0);
}

void ssd_vid_update() {
    if (ssdState == SSD_OFF) {
        /*Turn off SSD if status is off*/
        dio_vid_set_pin_value(SSD_ENABLE_1_PORT, SSD_ENABLE_1_PIN, SSD_OFF);
        dio_vid_set_pin_value(SSD_ENABLE_2_PORT, SSD_ENABLE_2_PIN, SSD_OFF);
        return;
    }
    u8 ones = ssdSymbol % 10;
    u8 tens = ssdSymbol / 10;
    /*toggle ssd 1, 2 status to print 2 digits*/
    if (dio_u8_read_pin_value(SSD_ENABLE_2_PORT, SSD_ENABLE_2_PIN) == SSD_ON) {
        dio_vid_set_pin_value(SSD_ENABLE_2_PORT, SSD_ENABLE_2_PIN, SSD_OFF);
        dio_vid_set_pin_value(SSD_ENABLE_1_PORT, SSD_ENABLE_1_PIN, SSD_ON);
        dio_vid_set_port_value(SSD_PORT, ssd_u8_get_code(tens));
    } else {
        dio_vid_set_pin_value(SSD_ENABLE_1_PORT, SSD_ENABLE_1_PIN, SSD_OFF);
        dio_vid_set_pin_value(SSD_ENABLE_2_PORT, SSD_ENABLE_2_PIN, SSD_ON);
        dio_vid_set_port_value(SSD_PORT, ssd_u8_get_code(ones));
    }
}

u8 ssd_u8_get_symbol() {
    
    return ssdSymbol;

}

void ssd_vid_set_symbol(u8 symbol) {
    ssdSymbol = symbol;
}

u8 ssd_u8_get_state(void) {
    return ssdState;
}

void ssd_vid_set_state(u8 state) {
    ssdState = state;
}


u8 ssd_u8_get_code(u8 number) {
    switch (number) {
        case 0:
            return 0x3F;
        case 1:
            return 0x06;
        case 2:
            return 0x5B;
        case 3:
            return 0x4F;
        case 4:
            return 0x66;
        case 5:
            return 0x6D;
        case 6:
            return 0x7D;
        case 7:
            return 0x07;
        case 8:
            return 0x7F;
        case 9:
            return 0x6F;
        default:
            return 0;
    }
}

