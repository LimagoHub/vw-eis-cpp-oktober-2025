/*
 * TimerUndFrequenz.c
 *
 * Created: 17.09.2024 12:31:24
 * Author : JoachimWagner
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMP_vect){
	
	PORTB ^=  0xFF;
}



int main(void)
{
	//y = 100;
	//register int x;
	DDRB = 0xFF;
	PORTB = 0;
	
	TCCR0 = (1 << WGM01); // CTC Modus
	OCR0 = 70;
	
	TIMSK = (1 << OCIE0);
	sei();
	TCCR0 |= (1 << CS02);
	
	
    /* Replace with your application code 
	
    while (1) 
    {
    }
}

