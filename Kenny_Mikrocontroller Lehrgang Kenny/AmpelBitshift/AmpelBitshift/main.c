/*
 * Ampel.c
 *
 * Created: 13.10.2025 12:22:20
 * Author : VW8GEET
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 255;
	DDRC = 255;
/*	uint8_t gruen = 0b00001000; //PORTB
	uint8_t gelb = 0b00000100; //PORTC
	uint8_t rot = 0b00001000; //PORTC
	uint8_t rotgelb = 0b00001100;
	uint8_t aus = 0; */

    while (1) 
    {
		PORTC |= (1 << PC3); //Oder für einschalten 00000001 zu 00001000
		_delay_ms(3000);
		PORTC &= ~(1 << PC3); //Und für auschalten 00001000 zu 00000000; ~ (Bitweise) für umdrehen aller 1 zu 0
		
		PORTC |= (1 << PC2) | (1 << PC3); //Ansteuern von 2 LEDS; 2 Bits werden geschoben
		_delay_ms(1000);
		PORTC &= ~(1 << PC2) & ~(1 << PC3);
		
		PORTB |= (1 << PB3);
		_delay_ms(3000);
		PORTB &= ~(1 << PB3);
		
		PORTC |= (1 << PC2) ;
		_delay_ms(1000);
		PORTC &= ~(1 << PC2);
    }
}
