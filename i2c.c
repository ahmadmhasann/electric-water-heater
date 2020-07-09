


/* 
 * File: i2c.c
 * Author: Ahmed Hassan
 * Created : July 7, 2020 
 */
#define _XTAL_FREQ 8000000 
#include <xc.h>
#include "macros.h"
#include "types.h"
#include "dio.h"
#include "i2c.h"

void i2c_vid_master_init(void) {

    dio_vid_set_pin_direction(C, SCL_PIN, INPUT_PIN);
    dio_vid_set_pin_direction(C, SDA_PIN, INPUT_PIN);

    SSPCON2 = 0x00;
    SSPSTAT = 0x00;

    /* Enables the serial port and configures the SDA and SCL pins as the serial port pins*/
    SSPEN  = 1;

    /* I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))*/
    SSPM3 = 1;
    SSPM2 = 0;
    SSPM1 = 0;
    SSPM0 = 0;

    /*Baud rate*/
    SSPADD = ((_XTAL_FREQ / 4) / I2C_BAUDRATE) - 1;
}

void i2c_vid_start(void) {
    i2c_vid_wait();
    /*Initiate Start condition on SDA and SCL pins. */
    SEN = 1;
}

void i2c_vid_stop(void) {
    i2c_vid_wait();
    /*Initiate Stop condition on SDA and SCL pins. */
    PEN = 1;
}

void i2c_vid_restart(void) {
    i2c_vid_wait();
    /*Initiate Repeated Start condition on SDA and SCL pins. */
    RSEN = 1;
}

void i2c_vid_wait(void) {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void i2c_vid_ack(void) {
    ACKDT = 0;
    i2c_vid_wait();
    ACKEN = 1;
}

void i2c_vid_nack(void) {
    ACKDT = 1;
    i2c_vid_wait();
    ACKEN = 1;
}

u8 i2c_u8_master_write_slave_address_with_write_req(u8 address) {
    i2c_vid_wait();
    /*address + write bit(0)*/
    SSPBUF = (address << 1);
    /*Wait Until Completion Flag*/
    while(!SSPIF);
    /*Clear flag*/
    SSPIF = 0;
    return ACKSTAT;
}

u8 i2c_u8_master_write_slave_address_with_read_req(u8 address) {
    i2c_vid_wait();
    /*address + read bit(1)*/
    SSPBUF = ( (address << 1) | 1);
    /*Wait Until Completion Flag*/
    while(!SSPIF);
    /*Clear flag*/
    SSPIF = 0;
    return ACKSTAT;
}

u8 i2c_u8_master_write_byte(u8 data) {
    i2c_vid_wait();
    SSPBUF = data;
    /*Wait Until Completion Flag*/
    while(!SSPIF);
    /*Clear flag*/
    SSPIF = 0;
    return ACKSTAT;
}

u8 i2c_u8_master_read_byte(void) {
    i2c_vid_wait();
    /*Enable & Start Receive*/
    RCEN = 1;
    /*Wait Until Completion Flag*/
    while(!SSPIF);
    /*Clear flag*/
    SSPIF = 0;
    i2c_vid_wait();
    return SSPBUF;
}
