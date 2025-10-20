/*
 * adc.c
 *
 * Created: 16.10.2025 08:50:15
 *  Author: Rechner Nr. 4
 */ 

#include "adc.h"

void adc_init()
{
	DDRA = 0;
	ADMUX = (1 << REFS0); // refs0 benutze 5v volt (betriebsspannung)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t adc_read(uint8_t channel)
{
	//ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	//ADCSRA |= (1 << ADSC);
	//while (ADCSRA & (1 << ADSC));
	//return ADC;
	
	ADMUX &= 0xf0;
	
	uint16_t result;
	ADMUX |= (channel & 0x0f);

	ADCSRA |= (1<<ADSC);
	while((ADCSRA&(1<<ADIF))==0);
		
	_delay_us(10);
	result =  ADCL;
	result  |= (ADCH << 8);
		
	return result;
}