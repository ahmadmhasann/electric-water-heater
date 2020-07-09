/*
 * File:   pwm.c
 * Author: Ahmed Hassan
 *
 * Created on July 9, 2020
 */
#define _XTAL_FREQ 8000000
#include <xc.h>
#include "types.h"
#include "dio.h"
#include "pwm.h"

void pwm_vid_init(u8 channel, u16 frequency) {

    /*Timer 2 prescaler = 16*/
    T2CKPS1 = 1;
    T2CKPS0 = 0;

    switch (channel) {
        case PWM_CHANNEL_1:
            /* PWM mode */
            CCP1M3 = 1;
            CCP1M2 = 1;
            /*Setting frequency*/
            PR2 = (_XTAL_FREQ / (frequency * 4 * 16));
            /*PWM pin output*/
            dio_vid_set_pin_direction(C, 2, OUTPUT_PIN);
            break;
        case PWM_CHANNEL_2:
            /* PWM mode */
            CCP2M3 = 1;
            CCP2M2 = 1;
            /*Setting frequency*/
            PR2 = (_XTAL_FREQ / (frequency * 4 * 16));
            /*PWM pin output*/
            dio_vid_set_pin_direction(C, 1, OUTPUT_PIN);
            break;
    }
}

void pwm_vid_start(void) {
    /*Enable timer 2*/
    TMR2ON = 1;
}

void pwm_vid_stop(u8 channel) {
    switch (channel) {
        case PWM_CHANNEL_1:
            CCP1M3 = 0;
            CCP1M2 = 0;
            break;

        case PWM_CHANNEL_2:
            CCP2M3 = 0;
            CCP2M2 = 0;
            break;
        default:
            break;    
    }
}

void pwm_vid_set_duty(u8 duty) {
    /*
     * PWM Duty Cycle =(CCPR1L:CCP1CON<5:4>) * TOSC * (TMR2 Prescale Value)
     * PWM Duty Cycle = 10bits * TOSC * (TMR2 Prescale Value)
     * 10bits = PWM Duty Cycle / (TOSC * (TMR2 Prescale Value))
     * 10bits = PWM Duty Cycle * _XTAL_FREQ / TMR2 Prescale Value
     * 10bits = PWM Duty Cycle * PR2 * 4
     * 10bits = PWM Duty Cycle * PR2 << 2 
     * CCPR1L = PWM Duty Cycle * PR2
     * CCP1X = 0
     * CCPY = 0
     * 
     */
    CCP1X = 0;
    CCP1Y = 0;
    CCPR1L = ((f32) duty / 100) * PR2;
}
