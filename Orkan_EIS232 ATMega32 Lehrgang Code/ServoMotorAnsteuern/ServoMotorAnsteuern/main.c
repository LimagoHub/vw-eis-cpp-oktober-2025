#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PB3);
	TCNT1 = 0;
	ICR1 = 311;
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS02) | (1 << CS00);
	
	while (1)
	{
		OCR1A = 8;   // ca. 1 ms (0°)
		_delay_ms(1500);
		OCR1A = 12;   // ca. 1.5 ms (90°)
		_delay_ms(1500);
		OCR1A = 16;   // ca. 2 ms (180°)
		_delay_ms(1500);
	}
}
