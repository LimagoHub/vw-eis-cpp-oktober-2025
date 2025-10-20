/*
 * Polling.c
 *
 * Created: 13.10.2025 14:16:45
 * Author : Rechner Nr. 4
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "macros.h"

int main(void)
{
	DDRD = 0; // PORT D auf eingang
	// PULLUP
	
	PORTD = (1 << PD2) | (1 << PD3); //Pull-Up Widerstand einstellen
	
	DDRB = (1 << PB0); //Port  B als Ausgang konfigurieren
	
	PORTB = (1 << PB0); // Bitshifting Operation für Port B
	
    while (1) 
    {
		if (GET_BIT(PIND, PD2) == 0) //Prüfen ob der Taster gedrückt ist (PD2)
		{
			//PORTB &= ~(1 << PB0); //LED ausschalten
			CLEAR_BIT(PORTB, PB0);
		}
		if (!GET_BIT(PIND, PD3)) //Prüfen ob der Taster gedrückt ist (PD3)
		{
			//PORTB |= (1 << PB0); //LED einschalten
			SET_BIT(PORTB, PB0);
		}
    }
}

