/*
 * File:   eeprom_external.c
 * Author: Hassan
 *
 * Created on July 7, 2020
 */
#include <xc.h>
#include "types.h"
#include "i2c.h"
#include "eeprom_external.h"    
void eeprom_external_vid_write(u8 address, u8 data) {
    i2c_vid_master_init();
    i2c_vid_start();
    while(i2c_u8_master_write_slave_address_with_write_req(EEPROM_ADDRESS))
    i2c_vid_restart();
    i2c_u8_master_write_byte(address >> 8);
    i2c_u8_master_write_byte((u8) address);
    i2c_u8_master_write_byte(data);
    i2c_vid_stop();
}
u8 eeprom_external_vid_read(u8 address) {
    i2c_vid_master_init();
    u8 data;
    i2c_vid_start();
    while(i2c_u8_master_write_slave_address_with_write_req(EEPROM_ADDRESS))
    i2c_vid_restart();
    i2c_u8_master_write_byte(address >> 8);
    i2c_u8_master_write_byte((u8) address);
    i2c_vid_restart();
    i2c_u8_master_write_slave_address_with_read_req(EEPROM_ADDRESS);
    data = i2c_u8_master_read_byte();
    i2c_vid_nack();
    i2c_vid_stop();
    return data;
}
