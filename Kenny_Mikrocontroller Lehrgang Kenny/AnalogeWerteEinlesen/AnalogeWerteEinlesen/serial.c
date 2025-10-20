#include "serial.h"

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

void serial_send_string(uint8_t * stringToSend) {
	while(*stringToSend) {
		serial_send_byte(* stringToSend ++);
	}
}
void serial_send_int(uint16_t * integerToSend){
		char buffer[10];
		itoa(integerToSend,buffer,10);
		serial_send_string(buffer);
}
void serial_send_float(float number, int width, int precision){
	char buffer[20];
	dtostrf(number,width,precision,buffer);
	serial_send_string(buffer);
}
