#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define S1 (1<<PD5)
#define S2 (1<<PD7)
#define S3 (1<<PD3)
#define S4 (1<<PD2)

int main(void)
{
    // pb1 als ausgang (oc0-pin für pwm)
    DDRB |= (1 << PB3);

    // taster als eingang
    DDRD = 0;

    // interne pull-ups aktivieren
    PORTD |= (S1 | S2 | S3 | S4);

    // fast pwm, non-inverting mode
    TCCR0 |= (1 << WGM00) | (1 << WGM01);
    TCCR0 |= (1 << COM01);

    // prescaler 8
    TCCR0 |= (1 << CS01);

    while (1)
    {
        if (!(PIND & S1))      
            OCR0 = 38;         // 15%
        else if (!(PIND & S2))
            OCR0 = 76;         // 30%
        else if (!(PIND & S3))
            OCR0 = 153;        // 60%
        else if (!(PIND & S4))
            OCR0 = 250;        // 100%

        _delay_ms(50);
    }
}
