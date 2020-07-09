
/**
 * 
 * timer.c
 * created by: Ahmed Hassan
 * created on July 6, 2020
 */


#define _XTAL_FREQ 8000000 
#include <xc.h>
#include "types.h"
#include "macros.h"
#include "dio.h"
#include "scheduler.h"
#include "timer.h"
void(*timer0_isr)(void);
void(*timer1_isr)(void);
void(*timer2_isr)(void);

void __interrupt() timer_isr() {
    if (TMR0IF == 1) {
        TMR0IF = 0;
        timer0_isr();
    }
    if (getBit(PIR1, TMR1IF) == 1) {
        clrBit(PIR1, TMR1IF);
        timer1_isr();
    }
    if (getBit(PIR1, TMR2IF) == 1) {
        clrBit(PIR1, TMR2IF);
        timer2_isr();
    }
}

void timer_vid_set_isr_0(void (*callback_function) (void)) {
    timer0_isr = callback_function;
}

void timer_vid_set_isr_1(void (*callback_function) (void)) {
    timer1_isr = callback_function;
}

void timer_vid_set_isr_2(void (*callback_function) (void)) {
    timer2_isr = callback_function;
}

void timer_vid_init_0(u16 prescaler, u8 interruptEnable) {

    /*Internal instruction cycle clock (CLKO)*/
    T0CS = 0;

    /*Prescaler is assigned to the Timer0 module*/
    PSA = 0;

    /*Prescaler Rate*/
    switch (prescaler) {
        case 2: 
            PS0 = 0;
            PS1 = 0;
            PS2 = 0;
            break;
        case 4:
            PS0 = 1;
            PS1 = 0;
            PS2 = 0;
            break;
        case 8:
            PS0 = 0;
            PS1 = 1;
            PS2 = 0;
            break;
        case 16:
            PS0 = 1;
            PS1 = 1;
            PS2 = 0;
            break;
        case 32:
            PS0 = 0;
            PS1 = 0;
            PS2 = 1;
            break;
        case 64:
            PS0 = 1;
            PS1 = 0;
            PS2 = 1;
            break;
        case 128:
            PS0 = 0;
            PS1 = 1;
            PS2 = 1;
            break;
        case 256:
            PS0 = 1;
            PS1 = 1;
            PS2 = 1;
            break;
    }

    if (interruptEnable) {
        /*Enable the Peripheral Interrupt*/
        PEIE = 1;

        /*Enable Global Interrupt*/
        GIE = 1;

        /*Enables Timer 0 Interrupt*/
        TMR0IE = 1;
    }
}
