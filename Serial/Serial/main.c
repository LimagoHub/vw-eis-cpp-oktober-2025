/*
 * Serial.c
 *
 * Created: 15.10.2025 09:39:21
 * Author : JoachimWagner
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#define BAUD 9600
#define MYUBRR ((F_CPU/(16UL*BAUD))-1)

int main(void)
{
    UBRRH = (uint8_t) (MYUBRR >> 8);
    UBRRL = (uint8_t) MYUBRR;
	
	UCSRB |= (1 << RXCIE);
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << UCSZ1) | (1 << UCSZ0) |(1 << URSEL); // Protokoll 8 Bit, keine Paritaet, 1 Stoppbit
	
    while (1) 
    {
		
		while ((UCSRA & (1 << RXC)) == 0){}
		uint8_t value = UDR;
		
		while (! (UCSRA & (1<<UDRE)));
		UDR = value;
    }
}

