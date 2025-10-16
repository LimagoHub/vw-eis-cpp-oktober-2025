/*
 * ADC.c
 *
 * Created: 16.10.2025 08:24:35
 * Author : JoachimWagner
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "serial.h"


int main(void)
{
    adc_init();
	serial_init();
	
    while (1) 
    {
		uint16_t value = adc_read(0);
		serial_send_int(value);
    }
}

