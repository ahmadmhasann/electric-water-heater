

/* 
 * File:   counter.h
 * Author: Ahmed Hassan
 * Created: July 8, 2020
 */

#ifndef COUNTER_H
#define	COUNTER_H

extern u8 buttonPressedFlag;
extern u8 settingModeFlag;
extern u16 settingModeCounter;
void counter_vid_init(void);
void counter_vid_update(void);
u8 counter_u8_get_counter (void);


#endif	

