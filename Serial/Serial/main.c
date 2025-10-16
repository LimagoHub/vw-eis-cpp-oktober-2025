/*
 * Serial.c
 *
 * Created: 15.10.2025 09:39:21
 * Author : JoachimWagner
 */ 


#include <avr/io.h>
#include "serial.h"
#include <stdlib.h>


void setUp() {
	
	serial_init();
	serial_send_string("\r\n");
	serial_send_float(23.69324, 5, 2);
	 
}
void loop() {
	
	uint8_t value = serial_get_byte();
	serial_send_byte(value);
	
}

int main(void)
{
   setUp();
    while (1) 
    {
	
		loop();
    }
}


