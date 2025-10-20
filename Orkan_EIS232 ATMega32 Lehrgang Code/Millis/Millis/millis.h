/*
 * millis.h
 *
 * Created: 17.10.2025 08:00:17
 *  Author: Rechner Nr. 4
 */ 


#ifndef MILLIS_H_
#define MILLIS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void millis_init();
uint64_t millis_getMillis();


#endif /* MILLIS_H_ */