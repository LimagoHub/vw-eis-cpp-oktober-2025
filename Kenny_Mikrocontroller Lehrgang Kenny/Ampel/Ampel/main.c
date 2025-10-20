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
	
	uint8_t gruen = 0b00001000; //PORTB
	uint8_t gelb = 0b00000100; //PORTC
	uint8_t rot = 0b00001000; //PORTC
	uint8_t rotgelb = 0b00001100;
	uint8_t aus = 0;
    while (1) 
    {
		PORTC = rot;
		_delay_ms(3000);
		PORTB = aus;
		PORTC = aus;
		
		PORTC = rotgelb;
		_delay_ms(1000);
		PORTB = aus;
		PORTC = aus;
		
		PORTB = gruen;
		_delay_ms(3000);
		PORTB = aus;
		PORTC = aus;
		
		PORTC = gelb;
		_delay_ms(1000);
		PORTB = aus;
		PORTC = aus;
		
    }
}

