/*
 * Millis.c
 *
 * Created: 17.10.2025 07:55:42
 * Author : JoachimWagner
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "millis.h"
int main(void)
{
	DDRB = 0b00000111;
    PORTB = (1 << PB0); 
	millis_init();
    while (1) 
    {
		PORTB |= (1 << PB0); 
		_delay_ms(2000);
		
		PORTB |= (1 << PB1);
		_delay_ms(500);
		
		PORTB &= 11111100;
		PORTB |= (1 << PB2);
		_delay_ms(2000);
		
		PORTB &= ~(1 << PB2);
		PORTB |= (1 << PB1);
		_delay_ms(500);
		
    }
}

