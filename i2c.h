

/* 
 * File: i2c.h
 * Author: Ahmed Hassan
 * Created : July 7, 2020 
 */


#ifndef I2C_H
#define	I2C_H

#define SCL_PIN 3
#define SDA_PIN 4
#define _XTAL_FREQ 8000000
#define I2C_BAUDRATE 9600
void i2c_vid_master_init(void);
void i2c_vid_start(void);
void i2c_vid_stop(void);
void i2c_vid_restart(void);
void i2c_vid_wait(void);
void i2c_vid_ack(void);
void i2c_vid_nack(void);
u8 i2c_u8_master_write_slave_address_with_write_req(u8 address);
u8 i2c_u8_master_write_slave_address_with_read_req(u8 address);
u8 i2c_u8_master_write_byte(u8 data);
u8 i2c_u8_master_read_byte(void);










#endif

