/*
 * lesenMitMacrosUndPolling.c
 *
 * Created: 14.10.2025 08:17:35
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
	
	
	SET_BIT(DDRB,PB0);
	
	SET_BIT(PORTB,PB0);
	
	while (1)
	{
		if(GET_BIT(PIND, PD2) == 0){
			CLEAR_BIT(PORTB,PB0);
		}
		if(! GET_BIT(PIND,PD3) ){
			SET_BIT(PORTB,PB0);
		}
	}
}

