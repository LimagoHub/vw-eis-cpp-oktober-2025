/*
 * SequentialLED.c
 *
 * Created: 13.10.2025
 * Author : Orkan & Corvin
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define ROT   (1 << PB0)
#define GELB  (1 << PB1)
#define GRUEN (1 << PB2)

int main(void)
{
	DDRB |= (ROT | GELB | GRUEN);
	PORTB &= ~(ROT | GELB | GRUEN);

	while (1)
	{
		PORTB |= ROT;
		PORTB &= ~(GELB | GRUEN);
		_delay_ms(3000);

		PORTB |= GELB;
		_delay_ms(1000);

		PORTB &= ~(ROT | GELB);
		PORTB |= GRUEN;
		_delay_ms(3000);

		PORTB &= ~GRUEN;
		PORTB |= GELB;
		_delay_ms(1000);
	}
}