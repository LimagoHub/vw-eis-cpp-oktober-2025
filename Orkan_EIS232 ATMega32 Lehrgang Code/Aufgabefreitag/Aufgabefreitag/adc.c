/*
 * adc.c
 *
 * Created: 14.09.2022 08:24:32
 *  Author: JoachimWagner
 */ 
#define F_CPU 8000000UL
#include "adc.h"
#include <util/delay.h>

void ADC_Init()
{
	DDRA=0x0;			
	ADCSRA = (1 << ADEN);			/* Enable ADC */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);			/* Set Prescaler */
	ADMUX = (1 << REFS0)	;		/* Vref: Avcc, ADC channel: 0 */
	
}

uint16_t ADC_Read(uint8_t channel)
{
	ADMUX &= 0xf0;  //  Reset channels
	
	uint16_t result;
	ADMUX |= (channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	result =  ADCL;		/* Read lower byte*/
	result  |= (ADCH << 8);	
		
	return result;			/* Return digital value*/
}