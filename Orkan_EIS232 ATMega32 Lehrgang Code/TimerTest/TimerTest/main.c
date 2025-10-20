#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB = 0xFF; // portb als ausgang
	
	TCCR0 |= (1 << WGM01); // timer0 in ctc-modus
	
	TCCR0 |= (1 << CS02); // prescaler
	
	OCR0 = 70; // wert für 440hz
	
	TIMSK |= (1 << OCIE0); // compare-match interrupt an
	
	sei(); // interrupts global an

	while (1)
	{
	}
}

ISR(TIMER0_COMP_vect)
{
	PORTB ^= 0xFF; // portb invertieren
}
