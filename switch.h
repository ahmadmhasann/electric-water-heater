/*
 * File:   switch.h
 * Author: Ahmed Hassan
 *
 * Created on July 9, 2020
 */
#ifndef SWITCH_H_
#define	SWITCH_H_

#define COOlER_PORT_ENABLE C
#define COOlER_PIN_ENABLE 2
#define HEATER_PORT_ENABLE C
#define HEATER_PIN_ENABLE 5

#define COOLER_ON 1
#define HEATER_ON 2
#define DEVICE_OFF 3
#define DEVICE_ON 4
#define ON_OFF_BUTTON 0

void switch_vid_init (void);
void switch_vid_update (void);
u8 switch_u8_get_state (void);


#endif

