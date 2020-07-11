

/* 
 * File:   display.h
 * Author: Ahmed Hassan
 * Created: July 8, 2020
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#define HEATER_ELEMENT_LED 6
#define DEVICE_ON_LED 7
#define DEVICE_SETTING_MODE_ON 1
#define DEVICE_SETTING_MODE_OFF 0

extern u8 displayFlag;
void display_vid_init (void);
void display_vid_update (void);
void display_vid_set_setting_mode_status (u8 mode);

#endif	

