#include "PWM.h"

void PWM_init(void)
{
	// Fast-PWM, nichtinvertiert, Prescaler 1024
	// WGM00=1, WGM01=1 -> Fast PWM
	// COM01=1 (nichtinvertiert), COM00=0
	// CS02=1, CS01=0, CS00=1 -> Prescaler 1024
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS02) | (1 << CS00);

	// OC0 (PB3) als Ausgang
	DDRB |= (1 << PB3);

	// Start mit Duty 0
	OCR0 = 0;
}

void PWM_set_duty(float duty_percent)
{
	// Bereich [0..100] klemmen
	if (duty_percent < 0.0)   duty_percent = 0.0;
	if (duty_percent > 100.0) duty_percent = 100.0;

	// Umrechnung Prozent -> 0..255
	// Hinweis: 100% -> 255 (volle Skala)
	OCR0 = (uint8_t)((duty_percent * 255.0) / 100.0);
}
