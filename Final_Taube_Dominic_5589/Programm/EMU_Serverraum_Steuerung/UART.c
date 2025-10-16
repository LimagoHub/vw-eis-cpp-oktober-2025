//////////////////////////////////////////////////////////////////////////////////////
// Name         : UART.c
// Beschreibung : Diese .c-Datei enthält Funktionen zur Kommunikation über UART
// Autor        : Rechner Nr. 5
// Erstellt     : 09.02.2023
//////////////////////////////////////////////////////////////////////////////////////

#include "UART.h"

//////////////////////////////////////////////////////////////////////////////////////
// Konfiguration
//////////////////////////////////////////////////////////////////////////////////////
#define Baud 9600
#define MYUBRR F_CPU/16/Baud - 1

#define wait_until_buffer_empty while ((UCSRA & (1 << RXC)) == 0)
#define wait_until_data_send    while (!(UCSRA & (1 << UDRE)))

//////////////////////////////////////////////////////////////////////////////////////
// Name         : UART_init
// Beschreibung : Initialisiert die UART-Schnittstelle mit 9600 Baud
// Parameter    : -
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void UART_init() {
	UBRRH = (MYUBRR >> 8);               // High-Byte der Baudrate
	UBRRL = MYUBRR;                      // Low-Byte der Baudrate

	UCSRB |= (1 << RXEN) | (1 << TXEN);  // Aktivieren von RX und TX
	UCSRB |= (1 << RXCIE);               // Aktivieren des RX-Interrupts
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-Bit-Daten, 1 Stopbit
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : UART_send
// Beschreibung : Sendet ein einzelnes Byte über UART
// Parameter    : uint8_t byte_to_send
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void UART_send(uint8_t byte_to_send) {
	wait_until_data_send;
	UDR = byte_to_send;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : UART_get_char
// Beschreibung : Empfängt ein einzelnes Byte über UART
// Parameter    : -
// Return       : uint8_t – empfangenes Byte
//////////////////////////////////////////////////////////////////////////////////////
uint8_t UART_get_char() {
	wait_until_buffer_empty;
	return UDR;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : UART_send_string
// Beschreibung : Sendet einen String über UART
// Parameter    : char* message – Zeiger auf Null-terminierten String
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void UART_send_string(char* message) {
	while (*message) {
		UART_send(*message++);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : UART_send_Integer
// Beschreibung : Wandelt eine Ganzzahl in einen String und sendet diesen über UART
// Parameter    : uint16_t two_byte_to_send – Zahl zwischen 0–65535
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void UART_send_Integer(uint16_t two_byte_to_send) {
	char buffer[10];
	itoa(two_byte_to_send, buffer, 10);
	UART_send_string(buffer);
}
