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
// Beschreibung : Aktiviert das Enable-Signal zum ?bertragen von Daten/Befehlen
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
// Parameter    : char* s ? Zeiger auf den String
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
// Parameter    : uint8_t c ? Zeichen
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_character(uint8_t c) {
	lcd_print(c, 1);
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_print
// Beschreibung : Sendet ein Byte (Befehl oder Daten) im 4-Bit-Modus
// Parameter    : uint8_t c ? Daten/Befehl
//                uint8_t rs ? 0 = Befehl, 1 = Daten
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
// Parameter    : uint8_t cmd ? LCD-Befehl
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

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_send_integer
// Beschreibung : Gibt eine Ganzzahl auf dem LCD aus
// Parameter    : int num ? Zahl, die ausgegeben werden soll
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_send_integer(int num)
{
	char buffer[12];
	itoa(num, buffer, 10);
	lcd_string(buffer);
}

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_send_float
// Beschreibung : Gibt eine Flie?kommazahl auf dem LCD aus
// Parameter    : float num ? Zahl, die ausgegeben werden soll
//                uint8_t nachkommastellen ? Anzahl der Dezimalstellen
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_send_float(float num, uint8_t nachkommastellen)
{
	char buffer[20];
	
	if (nachkommastellen > 6)
	nachkommastellen = 6;
	
	dtostrf(num, 0, nachkommastellen, buffer);
	
	lcd_string(buffer);
}

#define LCD_CMD_SET_DDRAM_ADDR  0x80  // cmd: setze ddram-adresse
#define LCD_LINE1_START         0x00  // startadresse der ersten zeile
#define LCD_LINE2_START         0x40  // startadresse der zweiten zeile

//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd_go_to_xy
// Beschreibung : Setzt den Cursor an eine bestimmte Position auf dem LCD
// Parameter    : x ? Spalte (0-basiert)
//                y ? Zeile  (0-basiert)
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void lcd_go_to_xy(uint8_t x, uint8_t y)
{
	uint8_t address;

	switch (y) {
		case 0: address = LCD_LINE1_START + x; break;
		case 1: address = LCD_LINE2_START + x; break;
		default: return;
	}

	lcd_command(LCD_CMD_SET_DDRAM_ADDR | address);
}