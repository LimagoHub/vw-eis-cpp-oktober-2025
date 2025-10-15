/*
 * LesenMitInterrupt.c
 *
 * Created: 14.10.2025 08:57:50
 * Author : JoachimWagner
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))


ISR(INT0_vect)  // haengt an Beinchen D2
{
	
	PORTB &= ~(1 << PB0);
}

ISR(INT1_vect) // haengt an Beinchen D3
{
	PORTB |= (1 << PB0);
	
}



int main(void)
{
	DDRD = 0;// PORT D auf eingang
	// PULLUP
	PORTD = (1 << PD2) | (1 << PD3);
	
	SET_BIT(DDRB,PB0);
	
	SET_BIT(PORTB,PB0);
	
	MCUCR |= (1 << ISC01) | (1 << ISC11);
	GICR = (1 << INT0) | (1 << INT1);
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

