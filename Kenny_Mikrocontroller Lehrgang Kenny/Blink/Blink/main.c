/*
 * Blink.c
 *
 * Created: 13.10.2025 09:23:13
 * Author : VW8GEET
 */ 
#define F_CPU 16000000UL //Taktfrequenz der CPU einstellen
#include <avr/io.h>
#include <util/delay.h> 

int main(void)
{
	DDRB = 255; // oder 0b11111111 für Binärzahl oder 0xFF für Hexadezimal (Data Direction Register)
	// Quasi pinMode(pin, input); oder output#
	DDRC = 255;
	PORTB = 255;
	PORTC = 0b00001100;
	// digitalWrite(pin, HIGH); Pins auf HIGH oder LOW setzen digital.
	_delay_ms(500);
	PORTB = 0;
	PORTC = 0;
    while (1) 
    {
	// nach links laufen
		for (uint8_t i = 0; i < 8; i++) {
		PORTB = (1 << i);
		_delay_ms(50);
		}
	// nach rechts laufen
		for (int8_t i = 6; i >= 1; i--) {
		PORTB = (1 << i);
		_delay_ms(50);
		}
    }
}