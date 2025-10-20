#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))

int main(void)
{
	// portb als ausgang
	DDRB = 0xFF;
	
	// pd2 und pd3 als eingang
	DDRD &= ~((1<<PD2) | (1<<PD3));
	
	// interne pull-ups an
	PORTD |= (1<<PD2) | (1<<PD3);

	// timer0 in ctc-modus
	TCCR0 |= (1 << WGM01);
	
	// prescaler 256
	//TCCR0 |= (1 << CS02);
	TCCR0 |= (1 << CS01) | (1 << CS00);
	
	// startfrequenz 1000 hz
	//OCR0 = 30;
	OCR0 = 124;
	
	// compare-match interrupt an
	TIMSK |= (1 << OCIE0);

	// externe interrupts konfigurieren
	MCUCR |= (1 << ISC01);
	
	MCUCR |= (1 << ISC11);
	
	GICR  |= (1 << INT0) | (1 << INT1);

	// interrupts global an
	sei();

	while (1)
	{
	}
}

// timer0 compare-match interrupt
ISR(TIMER0_COMP_vect)
{
	PORTB ^= 0xFF; 	// portb invertieren
}

// interrupt für int0 (pd2)
ISR(INT0_vect)
{
	//OCR0 = 30; // setzt frequenz auf 1000 hz
	OCR0 = 124;
}

// interrupt für int1 (pd3)
ISR(INT1_vect)
{
	//OCR0 = 61; // setzt frequenz auf 500 hz
	OCR0 = 248;	
}
