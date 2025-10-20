/*
 * ADC.h
 *
 * Created: 16.10.2025 08:46:13
 *  Author: VW8GEET
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <util/delay.h>
void ADC_Init();
uint16_t adc_read(uint8_t channel);




#endif /* ADC_H_ */