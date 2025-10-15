/*
 * Blink.c
 *
 * Created: 13.10.2025 09:22:26
 * Author : JoachimWagner
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = (1 << PB0); // Data Direction Register -> Bit gesetzt = ausgang
	PORTB = (1 << PB0);
    while (1) 
    {
		
		PORTB ^= (1 << PB0);
		_delay_ms(500);
    }
}

