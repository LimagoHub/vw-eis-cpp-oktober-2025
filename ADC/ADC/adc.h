/*
 * adc.h
 *
 * Created: 16.10.2025 08:45:50
 *  Author: JoachimWagner
 */ 


#ifndef ADC_H_
#define ADC_H_


#include <avr/io.h>

void adc_init() ;
uint16_t adc_read(uint8_t channel);



#endif /* ADC_H_ */