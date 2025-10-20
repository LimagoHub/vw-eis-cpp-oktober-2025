/*
 * LCD.c
 *
 * Created: 16.10.2025 10:29:26
 * Author : JoachimWagner
 */ 

#define F_CPU 16000000UL //Takt
#include <avr/io.h>
#include "LCD.h"
#include "ADC.h"
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMP_vect){
	PORTC ^= 0xFF;
}
int main(void) {
	ADC_Init();
    lcd_init();
	
	uint16_t valueOld1 = 0;
	float floatvalue1 = 0.0;
	
	DDRC = 0xFF;
	PORTC = 0;
	
	TCCR0 = (1 << WGM01);
	OCR0 = 2;
	
	TIMSK = (1 << OCIE0);
	sei();
	TCCR0 &= ~(1 << CS02);
	
	lcd_string("LCD wird");
	lcd_gotoxy(1,0);
	lcd_string("Initialisiert");
	_delay_ms(3000);
	lcd_command(CLEAR);
    while (1) {
		uint16_t value  = adc_read(0);
		floatvalue1 = value/1023.0*5.0;
		if (floatvalue1 >= 3.75) {
			lcd_gotoxy(0,0);
			lcd_float(floatvalue1,4,2);
			lcd_string(" V");
			lcd_gotoxy(1,0);
			lcd_string("ALARM!");
			lcd_string("                ");
			TCCR0 |= (1 << CS02);
		} else if (floatvalue1 >= 2.50) {
			lcd_gotoxy(0,0);
			lcd_float(floatvalue1,4,2);
			lcd_string(" V");
			lcd_gotoxy(1,0);
			lcd_string("Vorsicht!");
			lcd_string("                ");
			TCCR0 &= ~(1 << CS02);
		} else if (floatvalue1 >= 1.25) {
			lcd_gotoxy(0,0);
			lcd_float(floatvalue1,4,2);
			lcd_string(" V");
			lcd_gotoxy(1,0);
			lcd_string("Normal");
			lcd_string("                ");
		} else {
			lcd_gotoxy(0,0);
			lcd_float(floatvalue1,4,2);
			lcd_string(" V");
			lcd_gotoxy(1,0);
			lcd_string("Aus");
			lcd_string("                ");
		}
    }
}

