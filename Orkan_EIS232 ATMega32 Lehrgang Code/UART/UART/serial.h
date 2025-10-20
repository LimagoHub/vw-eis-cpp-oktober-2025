/*
 * serial.h
 *
 * Created: 15.10.2025 12:20:38
 *  Author: Rechner Nr. 4
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#define BAUD 9600
#define MYUBRR ((F_CPU/(16UL*BAUD))-1)

void serial_init();
uint8_t serial_get_byte();
void serial_send_byte(uint8_t byteToSend);
void serial_send_string(const char *str);
void serial_send_integer(uint16_t number);
void serial_send_float(float number, int width, int precision);

#endif /* SERIAL_H_ */