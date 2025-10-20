/*
 * millis.c
 *
 * Created: 17.10.2025 08:02:34
 *  Author: JoachimWagner
 */ 

#include "millis.h"

volatile static uint64_t _millis=0;
ISR(TIMER2_OVF_vect) {
	_millis ++;
}

void millis_init(){
	TCCR2 = (1 << CS22);
	TIMSK = (1 << TOIE2);
}
uint64_t millis_getMillis(){
	return _millis;
}
