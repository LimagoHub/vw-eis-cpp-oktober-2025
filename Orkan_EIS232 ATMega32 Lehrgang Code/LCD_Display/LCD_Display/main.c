/*
 * LCD_Display.c
 *
 * Created: 16.10.2025 12:21:30
 * Author : Rechner Nr. 4
 */ 

#include <avr/io.h>
#include "lcd.h"

int main(void)
{
	lcd_init();

	lcd_string("Hallo");
	
	lcd_go_to_xy(5, 1);
	lcd_string("Welt");
	while (1)
	{
		
	}
}

