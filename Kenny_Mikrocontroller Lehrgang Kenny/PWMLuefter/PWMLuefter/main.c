/*
 * PWMLuefter.c
 *
 * Created: 14.10.2025 13:52:30
 * Author : VW8GEET
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))

void PWM_init()
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS02) | (1<<CS00);
	DDRB|=(1<<PB3);  /*set OCR0 pin as output*/
}

int main(void)
{
	DDRD = 0; // alle Ports D auf Eingang
	PORTD = (1 << PD2) | (1 << PD3) | (1 << PD7) | (1 << PD5); //PULLUP konfigurieren aller Taster
	OCR0 = 0; //standart auf aus (0)
	PWM_init(); // PWM Initialisieren
    while (1) 
    {
		if(GET_BIT(PIND, PD2) == 0){ //Schalter S4 Abfragen ob auf GND gezogen wird
			OCR0 = 0;		//OCR0 auf Aus setzen
		}
		if (GET_BIT(PIND, PD3) == 0){//Schalter S3 Abfragen ob auf GND gezogen wird
			OCR0 = 77;		//OCR0 auf 30 Prozent setzen	
		}
		if(GET_BIT(PIND, PD7) == 0){ //Schalter S2 Abfragen ob auf GND gezogen wird
			OCR0 = 153;		//OCR0 auf 60 Prozent setzen	
		}
		if(GET_BIT(PIND, PD5) == 0){ //Schalter S1 Abfragen ob auf GND gezogen wird
			OCR0 = 250;		//OCR0 auf 99 Prozent setzen	(100 macht Probleme beim Oszi)
		}
    }
}