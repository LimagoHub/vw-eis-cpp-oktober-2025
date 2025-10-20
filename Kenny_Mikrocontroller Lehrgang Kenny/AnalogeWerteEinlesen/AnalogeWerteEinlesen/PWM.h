#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

/**
 * Initialisiert Timer0 in Fast-PWM, nichtinvertiert, Prescaler 1024.
 * Ausgang: OC0 (PB3) wird als Output gesetzt.
 */
void PWM_init(void);

/**
 * Setzt das Tastverh‰ltnis in Prozent [0..100].
 * Werte auﬂerhalb des Bereichs werden geklemmt.
 */
void PWM_set_duty(float duty_percent);

#endif // PWM_H
