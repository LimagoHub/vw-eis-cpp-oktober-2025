/*
 * millis.h
 *
 * Created: 17.10.2025 08:07:51
 *  Author: VW8GEET
 */ 

#ifndef MILLIS_H_
#define MILLIS_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void millis_init();
uint64_t millis_getMillis();

#endif /* MILLIS_H_ */