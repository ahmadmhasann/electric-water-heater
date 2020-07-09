/*
 * File:   eeprom_external.h
 * Author: Ahmed Hassan
 *
 * Created on July 8, 2020
 */

#ifndef EEPROM_EXTERNAL_H
#define	EEPROM_EXTERNAL_H

#define EEPROM_ADDRESS 0x50

void eeprom_external_vid_write(u8 address, u8 data);
u8 eeprom_external_vid_read(u8 address);

#endif	

