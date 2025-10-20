/*
 * pwm.h
 *
 * Created: 09.09.2022 09:42:22
 *  Author: JoachimWagner
 */ 
#pragma once
#include <avr/io.h>

#define NO_PRESCALING (1<<CS00) 
#define PRESCALE_1024 (1<<CS02)|(1<<CS00)

void pwm_init(uint8_t prescaler);
void pwm_set_duty(uint8_t duty);
uint8_t pwm_get_duty();