/*
 * RS232.c
 * Der Code initialisiert die UART, wartet auf ein empfangenes Byte, 
 * liest es ein und sendet es wieder zurück.
 * Created: 15.10.2025 10:08:45
 * Author : VW8GEET
 */ 

#include <avr/io.h>
#include "unterprogramme.h"
#include <stdlib.h>

int main(void)
{
	serial_init();
	serial_send_string("Hallo Welt\r\nHallo Welt 2\r\nHallo Welt 3");
	serial_send_string("\r\n");
	serial_send_int(8);
	serial_send_float(12.5555, 7, 2);
    while (1) 
    {
		uint8_t value = serial_get_byte();
		serial_send_byte(value);
    }
}