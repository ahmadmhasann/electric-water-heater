
/**
 * 
 * timer.h
 * created by: Ahmed Hassan
 * created on July 6, 2020
 */

#ifndef TIMER_H
#define	TIMER_H

void timer_vid_init_0(u16 prescaler, u8 interruptEnable);
void timer_vid_set_isr_0(void (*callback_function) (void));
void timer_vid_set_isr_1(void (*callback_function) (void));
void timer_vid_set_isr_2(void (*callback_function) (void));



#endif

