#include <avr/io.h>
#include <avr/interrupt.h>

#define SET_BIT(BYTE,BIT)   (BYTE |= (1 << BIT))
#define CLEAR_BIT(BYTE,BIT) (BYTE &= ~(1 << BIT))
#define TOGGLE_BIT(BYTE,BIT) (BYTE ^= (1 << BIT))
#define GET_BIT(BYTE,BIT)   (BYTE & (1 << BIT))

ISR(INT0_vect)
{
	CLEAR_BIT(PORTB, PB0);
}

ISR(INT1_vect)
{
	SET_BIT(PORTB, PB0);
}

int main(void)
{
	DDRD = 0;
	PORTD = (1 << PD2) | (1 << PD3);

	SET_BIT(DDRB, PB0);
	SET_BIT(PORTB, PB0);

	MCUCR &= ~((1 << ISC01) | (1 << ISC11));
	MCUCR |= (1 << ISC00) | (1 << ISC10);

	GICR |= (1 << INT0) | (1 << INT1);

	sei();

	while (1)
	{
	}

	return 0;
}
