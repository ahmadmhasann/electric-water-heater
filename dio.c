/*
 * dio.c
 *
 *  Created on: July 6, 2020
 *      Author: Ahmed Hassan
 */

#include "types.h"
#include "macros.h"
#include <xc.h>

void dio_vid_set_port_direction (u8 portNumber, u8 direction) {
	switch (portNumber) {
	case 0:
		TRISA = direction;
		break;
	case 1:
		TRISB = direction;
		break;
	case 2:
		TRISC = direction;
		break;
	case 3:
		TRISD = direction;
		break;
	case 4:
		TRISE = direction;
		break;
	}
}


void dio_vid_set_port_value (u8 portNumber, u8 value) {
	switch (portNumber) {
	case 0:
		PORTA = value;
		break;
	case 1:
		PORTB = value;
		break;
	case 2:
		PORTC = value;
		break;
	case 3:
		PORTD = value;
		break;
	case 4:
		PORTE = value;
		break;
	}
}

u8 dio_u8_read_port_value (u8 portNumber) {
	switch (portNumber) {
	case 0:
		return PORTA;
		break;
	case 1:
		return PORTB;
		break;
	case 2:
		return PORTC;
		break;
	case 3:
		return PORTD;
		break;
	case 4:
		return PORTE;
		break;
	}
	return 0;
}


u8 dio_u8_read_pin_value (u8 portNumber, u8 index) {
	u8 port = dio_u8_read_port_value(portNumber);
	return getBit(port, index);
}

void dio_vid_set_pin_value (u8 portNumber, u8 index, u8 value) {
	switch (portNumber) {
	case 0:
		if (value == 1)
			setBit(PORTA, index);
		else if (value == 0)
			clrBit(PORTA, index);
		break;
	case 1:
		if (value == 1)
			setBit(PORTB, index);
		else if (value == 0)
			clrBit(PORTB, index);
		break;
	case 2:
		if (value == 1)
			setBit(PORTC, index);
		else if (value == 0)
			clrBit(PORTC, index);
		break;
	case 3:
		if (value == 1)
			setBit(PORTD, index);
		else if (value == 0)
			clrBit(PORTD, index);
		break;
	case 4:
		if (value == 1)
			setBit(PORTE, index);
		else if (value == 0)
			clrBit(PORTE, index);
		break;
	}
}


void dio_vid_set_pin_direction (u8 portNumber, u8 index, u8 direction) {
	switch (portNumber) {
	case 0:
		if (direction == 1)
			setBit(TRISA, index);
		else if (direction == 0)
			clrBit(TRISA, index);
		break;
	case 1:
		if (direction == 1)
			setBit(TRISB, index);
		else if (direction == 0)
			clrBit(TRISB, index);
		break;
	case 2:
		if (direction == 1)
			setBit(TRISC, index);
		else if (direction == 0)
			clrBit(TRISC, index);
		break;
	case 3:
		if (direction == 1)
			setBit(TRISD, index);
		else if (direction == 0)
			clrBit(TRISD, index);
		break;
	case 4:
		if (direction == 1)
			setBit(TRISE, index);
		else if (direction == 0)
			clrBit(TRISE, index);
		break;
	}
}
