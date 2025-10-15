/*
 * LesenMitPolling.c
 *
 * Created: 13.10.2025 13:53:57
 * Author : JoachimWagner
 */ 

#include <avr/io.h>

#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))

int main(void)
{
    DDRD = 0;// PORT D auf eingang
	// PULLUP
	PORTD = (1 << PD2) | (1 << PD3);
	
	DDRB = (1 << PB0);
	
	PORTB =   (1 << PB0);
	
    while (1) 
    {
		if((PIND & (1 << PD2)) == 0){
			PORTB &= ~(1 << PB0);
		}
		if(! (PIND & (1 << PD3)) ){
			SET_BIT(PORTB,PB0);
		}
	}
}

