/*
 * Millis.c
 *
 * Created: 17.10.2025 08:07:25
 * Author : VW8GEET
 */ 
#include "millis.h"

int main(void)
{
    DDRB = 0b00000111;
	PORTB = (1 << PB0);
	millis_init();
	uint64_t millis_aktuell;

    while (1) 
    {
		switch (4) {
			case 0: break;
			case 1: break;
			case 2: break;
			case 3: break;
		} 
		PORTB |= (1 << PB0);
		millis_getMillis(2000);
		
		PORTB |= (1 << PB1);
		millis_getMillis(2000);
		
		PORTB &= 11111100;
		PORTB|= (1 << PB2);
		millis_getMillis(2000);
		
		PORTB &= ~(1 << PB2);
		PORTB |= (1 << PB1);
		millis_getMillis(500);
		
    }
}

