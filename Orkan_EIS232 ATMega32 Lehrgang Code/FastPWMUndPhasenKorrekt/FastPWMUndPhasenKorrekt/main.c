#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define S1 (1 << PD2)

#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))

int main(void)
{
	// pb3 als ausgang (oc0)
	DDRB |= (1 << PB3);

	// taster pd2 als eingang mit pull-up
	DDRD &= ~S1;
	PORTD |= S1;

	// start im ctc-modus mit toggle auf oc0
	TCCR0 = 0;
	TCCR0 |= (1 << WGM01) | (1 << COM00); // ctc + toggle
	TCCR0 |= (1 << CS01);                 // prescaler 8

	// vergleichswert für rechtecksignal
	OCR0 = 124; // etwa 8 kHz bei f_cpu 16 MHz, prescaler 8

	uint8_t mode = 0; // 0 = ctc (rechteck), 1 = phase correct pwm

	while (1)
	{
		if (!(PIND & S1)) // taster gedrückt?
		{
			_delay_ms(50); // entprellung

			if (mode == 0)
			{
				// phase correct pwm (pwm-signal)
				TCCR0 = 0;
				TCCR0 |= (1 << WGM00);   // phase correct
				TCCR0 |= (1 << COM01);   // non-inverting
				TCCR0 |= (1 << CS01);    // prescaler 8
				OCR0 = 128;              // 50% tastgrad
				mode = 1;
			}
			else
			{
				// zurück zu ctc-toggle (rechteck)
				TCCR0 = 0;
				TCCR0 |= (1 << WGM01) | (1 << COM00);
				TCCR0 |= (1 << CS01);    // prescaler 8
				OCR0 = 124;
				mode = 0;
			}

			// warten bis losgelassen
			while (!(PIND & S1));
			_delay_ms(50);
		}
	}
}
