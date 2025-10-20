/*
 * adc.h
 *
 * Created: 14.09.2022 08:22:19
 *  Author: JoachimWagner
 */ 

#pragma once 
#include <avr/io.h>

void ADC_Init();
uint16_t ADC_Read(uint8_t channel);

