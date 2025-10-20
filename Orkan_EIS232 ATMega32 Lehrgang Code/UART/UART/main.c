/*
 * UART.c
 *
 * Created: 15.10.2025 09:40:12
 * Author : Rechner Nr. 4
 */ 

#include "serial.h"

int main(void)
{
	serial_init();
	
	
    while (1) 
    {
		uint8_t value = serial_get_byte();
		serial_send_byte(value);
		
		serial_send_string("Ich liebe ATMega32 Programmierung!\n");
    }
}

