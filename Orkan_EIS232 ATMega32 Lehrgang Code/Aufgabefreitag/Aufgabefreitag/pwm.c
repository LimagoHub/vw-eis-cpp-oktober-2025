/*
 * pwm.c
 *
 * Created: 09.09.2022 09:47:29
 *  Author: JoachimWagner
 */ 
#include "pwm.h"

void pwm_init(uint8_t prescaler)
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | prescaler;
	DDRB|=(1<<PB3);  /*set OC0 pin as output*/
}

void pwm_set_duty(uint8_t duty) {
	OCR0 = duty;
}

uint8_t pwm_get_duty(){
	return OCR0;
}