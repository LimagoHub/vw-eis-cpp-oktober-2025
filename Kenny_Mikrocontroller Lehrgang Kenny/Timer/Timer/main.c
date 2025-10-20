/*
 * Timer.c
 *
 * Created: 14.10.2025 10:08:44
 * Author : VW8GEET
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMP_vect) //Interrupt // CTC Mode COMP wegen WGM01, bei nicht setzen Normal mode (WGM00)
{
	PORTB = ~PORTB; //Toggelt Port B (Alle Beinchen)
}
int main(void)
{
	TCCR0 |= (1 << WGM01);  //Setzen auf CTC Mode im TCC Register
	OCR0 = 61; //Vergleichsregister bis zu dem der Counter hoch zaehlt, bis er 61 erreicht hat und dann Interrupt setzen
	DDRB = 0xFF; //Pins im B Register alle auf Ausgang setzen
	TIMSK |= (1 << OCIE0); //Nur Sinn im CTC Mode; OCIE0 für Compare (ISR hat COMP); TOIE0 für Ueberlauf (ISR hat OVF)
	sei(); //Interrupt Global aktivieren
	TCCR0 |= (1 << CS02); //Timer starten; Alle Bits 0 Stopp (CS02,CS01,CS00), CS02 auf 1 setzen (zaehlt nur jeden 256 Tackt)
    while (1) 
    {

    }
}

