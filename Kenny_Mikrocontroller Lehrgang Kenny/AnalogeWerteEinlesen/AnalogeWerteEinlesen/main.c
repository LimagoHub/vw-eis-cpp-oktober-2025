#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ADC.h"
#include "serial.h"
#include "PWM.h"  

#define TOLERANZ 5

int main(void)
{
	DDRD = 0;
	PORTD = (1 << PD2) | (1 << PD3) | (1 << PD7) | (1 << PD5);

	PWM_init();        
	ADC_Init();
	serial_init();

	uint16_t valueOld1 = 0;
	uint16_t valueOld2 = 0;
	float floatvalue1 = 0.0;
	float floatvalue2 = 0.0;

	while (1)
	{
		uint16_t value  = adc_read(0);
		uint16_t value2 = adc_read(1);

		if (abs(value - valueOld1) > TOLERANZ) {
			serial_send_string("Analogwert 1: ");
			serial_send_int(value);
			serial_send_string(" ");
			serial_send_string("Spannungswert 1: ");
			floatvalue1 = value / 1023.0 * 5.0;
			serial_send_float(floatvalue1, 4, 2);
			serial_send_string("V\r\n");
			valueOld1 = value;
		}

		if (abs(value2 - valueOld2) > TOLERANZ) {
			serial_send_string("Analogwert 2: ");
			serial_send_int(value2);
			serial_send_string(" ");
			serial_send_string("Spannungswert 2: ");
			floatvalue2 = value2 / 1023.0 * 5.0;
			serial_send_float(floatvalue2, 4, 2);
			serial_send_string("V\r\n");
			valueOld2 = value2;
		}

		if (floatvalue1 >= 3.75) {
				PWM_set_duty(100);
			} else if (floatvalue1 >= 2.50) {
				PWM_set_duty(66);
			} else if (floatvalue1 >= 1.25) {
				PWM_set_duty(33);
			} else {
				PWM_set_duty(0);
		}
	}
}
