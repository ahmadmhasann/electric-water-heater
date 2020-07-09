

/* 
 * File:   display.h
 * Author: Ahmed Hassan
 * Created: July 8, 2020
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#define HEATER_ON_PIN 3
#define COOLER_ON_PIN 4
#define DEVICE_STATE_PIN 5
#define DEVICE_SETTING_MODE_ON 1

extern u8 displayFlag;
void display_vid_init (void);
void display_vid_update (void);
void display_set_setting_mode (u8 mode);

#endif	

