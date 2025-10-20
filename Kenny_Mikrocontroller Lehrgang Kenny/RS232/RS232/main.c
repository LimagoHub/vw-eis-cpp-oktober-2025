/*
 * RS232.c
 * Der Code initialisiert die UART, wartet auf ein empfangenes Byte, 
 * liest es ein und sendet es wieder zurück.
 * Created: 15.10.2025 10:08:45
 * Author : VW8GEET
 */ 

#define F_CPU 16000000UL //Takt
#include <avr/io.h>
#define BAUD 9600 //Einstellung der Baudrate
#define MYUBRR ((F_CPU/(16UL*BAUD))-1) //Berechnung des Formelwert für das Register

void serial_init() {
	UBRRH = (uint8_t) (MYUBRR >> 8); //Baudrate High setzen
	UBRRL = (uint8_t) MYUBRR; //Baudrate Low setzen
	
	UCSRB |= (1 << RXCIE); //RX-Interrupt aktivieren
	UCSRB |= (1 << RXEN) | (1 << TXEN); //RX und TX aktivieren
	UCSRB |= (1 << UCSZ1) | (1 << UCSZ0) | (1 << URSEL); //8-Bit Protokoll,keine Parität, 1 Stopp
}

uint8_t serial_get_byte() {
	while ((UCSRA & (1 << RXC)) == 0) {} //Warteschleife; Wartet auf Empfganspuffer (Daten empfangen)
	
	return UDR; //Lesen der Empfangenen Daten
}

void serial_send_byte(uint8_t byteToSend) {
	while (! (UCSRA & (1 << UDRE))); //Warteschleife; Wartet auf freien Sendepuffer
	
	UDR = byteToSend; //Echo, sendet Daten zurück
}

void setUp() {
	serial_init();
}

void loop() {
	uint8_t value = serial_get_byte();
	serial_send_byte(value);
}

int main(void)
{
    while (1) 
    {
	loop();
    }
}

