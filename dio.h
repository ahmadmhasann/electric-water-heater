/*
 * dio.h
 *
 *  Created on: July 6, 2020
 *      Author: Ahmed Hassan
 */
#ifndef DIO_H_
#define DIO_H_

enum {
	A,
	B,
	C,
	D,
    E
};
#define OUTPUT_PORT 0x00
#define INPUT_PORT 0xFF

#define OUTPUT_PIN 0x00
#define INPUT_PIN 0x01

#define HIGH_PORT 0xFF
#define LOW_PORT 0x00

#define HIGH_PIN 0x01
#define LOW_PIN 0x00


void dio_vid_set_port_direction (u8 portNumber, u8 direction);
void dio_vid_set_port_value (u8 portNumber, u8 value);
u8 dio_u8_read_port_value (u8 portNumber);
u8 dio_u8_read_pin_value (u8 portNumber, u8 index);
void dio_vid_set_pin_value (u8 portNumber, u8 index, u8 value);
void dio_vid_set_pin_direction (u8 portNumber, u8 index, u8 direction);

#endif /* DIO_H_ */


