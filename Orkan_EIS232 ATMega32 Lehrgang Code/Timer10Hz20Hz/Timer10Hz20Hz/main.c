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

	// timer1 in ctc-modus
	TCCR1B |= (1 << WGM12);						//Der ctc-Modus hat jetzt den Wert "WGM12" und nicht mehr "WGM01"
	
	// prescaler 256
	TCCR1B |= (1 << CS12);						//Der Prescaler hat jetzt den Wert "CS12" und nicht mehr "CS02"
	
	// startfrequenz 20 hz
	OCR1A = 1559;
	
	// compare-match interrupt an
	TIMSK |= (1 << OCIE1A);

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

// timer1 compare-match interrupt
ISR(TIMER1_COMPA_vect)							//Nutzen von COMPA statt COMP
{
	PORTB ^= 0xFF;	// portb invertieren
}

// interrupt für int0 (pd2)
ISR(INT0_vect)
{
	//OCR1A = 1559; // setzt frequenz auf 20 hz
	OCR1A = 1559;								//Nutzen von OCR1A statt OCR0
}

// interrupt für int1 (pd3)
ISR(INT1_vect)
{
	//OCR1A = 3124; // setzt frequenz auf 10 hz
	OCR1A = 3124;								//Nutzen von OCR1A statt OCR0
}
