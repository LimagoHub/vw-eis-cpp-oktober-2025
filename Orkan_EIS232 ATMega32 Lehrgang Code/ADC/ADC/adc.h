/*
 * adc.h
 *
 * Created: 16.10.2025 08:46:44
 *  Author: Rechner Nr. 4
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>

void adc_init();
uint16_t adc_read(uint8_t channel);

#endif /* ADC_H_ */