
/*
 * File:   adc.c
 * Author: Ahmed Hassan
 *
 * Created on July 9, 2020
 */
#define _XTAL_FREQ 8000000 
#include <xc.h>
#include "types.h"
#include "adc.h"

void adc_vid_init (void) {
  
    /* A/D Conversion Clock FOSC/2*/
    ADCS2 = 0;
    ADCS1 = 0;
    ADCS0 = 0;
    
    /*Right justified*/
    ADFM = 1;
}


u16 adc_u8_get_value (u8 channel) {
    
    /*A/D converter module is powered up*/
    ADON = 1;
    
    /*Clear previous channel*/
    ADCON0 &= 0b11000111;
    
    /*Set new channel*/
    ADCON0 |= channel<<3;
    __delay_ms(1);
    
    /*Start ADC conversion*/
    GO = 1;
    
    /*wait until done*/
    while (GO_DONE == 1);
    
    /*A/D converter module is shut-off*/
    ADON = 0;
    
    /*return result*/
    return((ADRESH<<8) + ADRESL);
}
