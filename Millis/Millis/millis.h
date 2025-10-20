/*
 * millis.h
 *
 * Created: 17.10.2025 07:59:00
 *  Author: JoachimWagner
 */ 


#ifndef MILLIS_H_
#define MILLIS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void millis_init();
uint64_t millis_getMillis();



#endif /* MILLIS_H_ */