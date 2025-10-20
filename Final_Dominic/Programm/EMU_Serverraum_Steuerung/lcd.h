//////////////////////////////////////////////////////////////////////////////////////
// Name         : lcd.h
// Beschreibung : Header-Datei für LCD-Ansteuerung im 4-Bit-Modus
// Autor        : Rechner Nr. 6
// Erstellt     : 11.11.2024
//////////////////////////////////////////////////////////////////////////////////////

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// === Steuerleitungen am Port B ===
#define RS PB0     // Register Select
#define E  PB2     // Enable

// === LCD-Kommandos ===
#define LCD_ON         0x0E
#define LCD_OFF        0x08
#define CLEAR          0x01
#define ENTRY_MODE     0x06
#define FOURBITE_MODE  0x20
#define TWO_LINES      0x28
#define FORCE_SND_LINE 0xC0

// === Funktionsprototypen ===
void lcd_enable(void);
void lcd_init(void);
void lcd_string(char* s);
void lcd_character(volatile uint8_t c);
void lcd_print(uint8_t c, uint8_t rs);
void lcd_command(uint8_t cmd);

#endif /* LCD_H_ */
