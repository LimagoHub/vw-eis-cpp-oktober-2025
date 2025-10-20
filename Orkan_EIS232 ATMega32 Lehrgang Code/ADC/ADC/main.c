/*
 * ADC_PWM.c
 *
 * Created: 16.10.2025
 * Author : Rechner Nr. 4
 */ 

#include <avr/io.h>
#include "adc.h"
#include "serial.h"

void pwm_init(void) {
	DDRB |= (1 << PB3);
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);
}

void pwm_setDuty(float dutyPercent) {
	if (dutyPercent > 100) dutyPercent = 100;
	OCR0 = (uint8_t)((dutyPercent / 100.0) * 255);
}

int main(void) {
	adc_init();
	serial_init();
	pwm_init();

	while (1) {
		uint16_t value = adc_read(0);
		float voltage = (value / 1023.0) * 5.0;
		uint8_t duty = 0;

		if (voltage <= 1.25)
			duty = 0;
		else if (voltage <= 2.5)
			duty = 30;
		else if (voltage <= 3.75)
			duty = 60;
		else
			duty = 100;

		pwm_setDuty(duty);

		serial_send_float(voltage, 4, 2);
		serial_send_string(" V  PWM: ");
		serial_send_integer(duty);
		serial_send_string("%\r\n");
	}
}
