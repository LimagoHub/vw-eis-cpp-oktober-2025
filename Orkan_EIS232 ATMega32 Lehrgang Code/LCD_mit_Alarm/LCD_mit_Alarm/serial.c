/*
 * serial.c
 *
 * Created: 15.10.2025 12:22:39
 *  Author: Rechner Nr. 4
 */ 

#include "serial.h"

void serial_init()
{
	UBRRH = (uint8_t) (MYUBRR >> 8);
	UBRRL = (uint8_t) MYUBRR;
	
	UCSRB |= (1 << RXCIE);
	UCSRB |= (1 << RXEN) |(1 << TXEN);
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0) | (1 << URSEL); //Protokoll 8 Bit, keine Paritaet, 1 Stoppbit
}

uint8_t serial_get_byte()
{
	while ((UCSRA & (1 << RXC)) == 0) {}
	return UDR;
}

void serial_send_byte(uint8_t byteToSend)
{
	while (! (UCSRA & (1<<UDRE)));
	UDR = byteToSend;
}

void serial_send_string(const char *str)
{
	while (*str != '\0')    // null terminator
	{
		serial_send_byte(*str);
		str++;
	}
}

void serial_send_integer(uint16_t number)
{
	char buffer[6];
	utoa(number, buffer, 10);
	serial_send_string(buffer);
}

void serial_send_float(float number, int width, int precision)
{
	char buffer[20];
	dtostrf(number, width, precision, buffer);
	serial_send_string(buffer);
}