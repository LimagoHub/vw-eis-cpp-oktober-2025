/*
 * TasterEinlesen.c
 *
 * Created: 13.10.2025 13:54:10
 * Author : VW8GEET
 */ 
#define F_CPU 160000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))

int main(void)
{
    DDRD = 0; // Port D auf Eingang
	PORTD = (1 << PD2) | (1 << PD3); //PULLUP konfigurieren

	// DDRB = (1 << PB0); //LED PB0 auf Ausgang
	SET_BIT(DDRB, PB0);
	// PORTB = (1 << PB0); //LED PB0 an machen
	SET_BIT(PORTB, PB0);
	
    while (1) //unendliche Schleife da 1 (true)
    {
		if(GET_BIT(PIND, PD2) == 0){
			CLEAR_BIT(PORTB, PB0);	
		}
		if (! GET_BIT(PIND, PD3) ){
			SET_BIT(PORTB, PB0);
		}
/*		if((PIND & (1 << PD2)) == 0) { //Prüfe ob PD2 gedrückt wird (auf GND gezogen wird) 
			PORTB &= ~(1 << PB0); //LED PB0 an machen
		}	
		if(! (PIND & (1 << PD3)) ) { //Prüfe ob PD3 gedrückt wird (auf GND gezogen wird)
			PORTB |= (1 << PB0); //LED PD0 aus machen
			}	*/
    }
}

