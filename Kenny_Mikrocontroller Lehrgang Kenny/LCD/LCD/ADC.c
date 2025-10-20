/*
 * ADC.c
 *
 * Created: 16.10.2025 08:48:05
 *  Author: VW8GEET
 */ 
#include "ADC.h"

void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) ;			/* Enable ADC, fr/128  */
	ADMUX = (1 << REFS0);			/* Vref: Avcc, ADC channel: 0 */
}
uint16_t adc_read(uint8_t channel) {
	uint16_t result;
	
	ADMUX &= 0xF0;
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	result = (uint16_t) ADCL;
	result |= (uint16_t) (ADCH << 8);
	
	return result;
}