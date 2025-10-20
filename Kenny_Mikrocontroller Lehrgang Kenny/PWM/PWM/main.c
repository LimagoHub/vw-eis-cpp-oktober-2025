/*
 * PWM.c
 *
 * Created: 14.10.2025 13:39:34
 * Author : VW8GEET
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void PWM_init(void)
{
    /* Fast PWM, nicht-invertiert, Prescaler = 1 */
    TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
    DDRB |= (1<<PB3);  /* OC0 als Ausgang */
}

int main(void)
{
    char richtung = 1;  // 1 = hochzählen, -1 = runterzählen

    PWM_init();

    while (1)
    {
        _delay_ms(5);

        OCR0 += richtung;

        if (OCR0 == 255) richtung = -1; // wenn Maximum erreicht -> runter
        if (OCR0 == 0)   richtung =  1; // wenn Minimum erreicht -> hoch
    }
}