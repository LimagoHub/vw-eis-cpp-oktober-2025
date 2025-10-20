/*
 * Millis.c
 *
 * Created: 17.10.2025 08:00:06
 * Author : Rechner Nr. 4
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "millis.h"

typedef enum {
	ROT,
	GELB_NACH_ROT,
	GRUEN,
	GELB_NACH_GRUEN
} AmpelState;

int main(void)
{
	DDRB = 0b00000111;
	PORTB = (1 << PB0);
	
	millis_init();
	sei();

	AmpelState state = ROT;
	uint64_t previousMillis = millis_getMillis();

	while (1)
	{
		uint64_t currentMillis = millis_getMillis();

		switch (state)
		{
			case ROT:
			PORTB = (1 << PB0);
			if (currentMillis - previousMillis >= 2000) {
				previousMillis = currentMillis;
				PORTB &= ~(1 << PB0);
				state = GELB_NACH_ROT;
			}
			break;

			case GELB_NACH_ROT:
			PORTB = (1 << PB1);
			if (currentMillis - previousMillis >= 500) {
				previousMillis = currentMillis;
				PORTB &= ~(1 << PB1);
				state = GRUEN;
			}
			break;

			case GRUEN:
			PORTB = (1 << PB2);
			if (currentMillis - previousMillis >= 2000) {
				previousMillis = currentMillis;
				PORTB &= ~(1 << PB2);
				state = GELB_NACH_GRUEN;
			}
			break;

			case GELB_NACH_GRUEN:
			PORTB = (1 << PB1);
			if (currentMillis - previousMillis >= 500) {
				previousMillis = currentMillis;
				PORTB &= ~(1 << PB1);
				state = ROT;
			}
			break;
		}
	}
}