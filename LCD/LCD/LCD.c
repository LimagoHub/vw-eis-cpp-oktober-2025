/*
 * LCD.c
 *
 * Created: 16.10.2025 10:31:33
 *  Author: JoachimWagner
 */ 


#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_enable
// Beschreibung : Aktiviert das Enable-Signal zum Übertragen von Daten/Befehlen
// Parameter    : -
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_enable() {
	PORTB |= (1 << E);
	_delay_ms(1);
	PORTB &= ~(1 << E);
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_string
// Beschreibung : Gibt einen String auf dem LCD aus
// Parameter    : char* s – Zeiger auf den String
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_string(char* s) {
	while (*s) {
		lcd_character(*s++);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_character
// Beschreibung : Gibt ein einzelnes Zeichen auf dem LCD aus
// Parameter    : uint8_t c – Zeichen
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_character(uint8_t c) {
	lcd_print(c, 1);
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_print
// Beschreibung : Sendet ein Byte (Befehl oder Daten) im 4-Bit-Modus
// Parameter    : uint8_t c – Daten/Befehl
//                uint8_t rs – 0 = Befehl, 1 = Daten
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_print(uint8_t c, uint8_t rs) {
	uint8_t high_nibble = c & 0xF0;
	uint8_t low_nibble = (c << 4) & 0xF0;

	PORTB = high_nibble | (rs ? (1 << RS) : 0);
	lcd_enable();
	PORTB = low_nibble | (rs ? (1 << RS) : 0);
	lcd_enable();

	_delay_ms(2);
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_command
// Beschreibung : Sendet einen LCD-Befehl
// Parameter    : uint8_t cmd – LCD-Befehl
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_command(uint8_t cmd) {
	lcd_print(cmd, 0);
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_init
// Beschreibung : Initialisiert das LCD-Display im 4-Bit-Modus
// Parameter    : -
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_init() {
	DDRB = 0xFF;
	_delay_ms(50);

	PORTB = 0x30;
	lcd_enable();
	_delay_ms(15);
	lcd_enable();
	_delay_ms(100);
	lcd_enable();

	PORTB = FOURBITE_MODE;
	lcd_enable();
	_delay_ms(1);

	lcd_command(TWO_LINES);
	lcd_command(ENTRY_MODE);
	lcd_command(LCD_OFF);
	lcd_command(CLEAR);
	_delay_ms(5);
	lcd_command(LCD_ON);
}

