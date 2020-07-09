/*
 * File:   pwm.h
 * Author: Ahmed Hassan
 *
 * Created on July 9, 2020
 */

#ifndef PWM_H_
#define	PWM_H_

#define PWM_CHANNEL_1 1
#define PWM_CHANNEL_2 2

void pwm_vid_init(u8 channel, u16 frequency);
void pwm_vid_start(void);
void pwm_vid_stop(u8 channel);
void pwm_vid_set_duty(u8 duty);



#endif	

