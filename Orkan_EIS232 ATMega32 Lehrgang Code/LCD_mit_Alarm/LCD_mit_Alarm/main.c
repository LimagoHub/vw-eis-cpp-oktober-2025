#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "serial.h"
#include "LCD.h"

#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))

ISR(TIMER0_COMP_vect) {
    PINC = (1 << PC0);
}

void timer0_init_440Hz(void) {
	TCCR0 = (1 << WGM01) | (1 << CS02); // CTC-Modus, Prescaler 256
	OCR0 = 70;
	TIMSK |= (1 << OCIE0); // Interrupt Compare Match Enable
}

void timer0_start(void) {
    TCNT0 = 0;
    TIMSK |= (1 << OCIE0);
}

void timer0_stop(void) {
    TIMSK &= ~(1 << OCIE0);
    PORTC &= ~(1 << PC0);
}

int main(void)
{
    adc_init();
    serial_init();
    lcd_init();

    DDRC |= (1 << PC0);
    PORTC &= ~(1 << PC0);

    timer0_init_440Hz();
    sei();

    while (1) {
        uint16_t value = adc_read(0);
        float voltage = (value / 1023.0) * 5.0;

        if (voltage < 2.0) {
            lcd_string("Alles tutti frutti...   ");
            timer0_stop();
        }
        else if (voltage < 4.0) {
            lcd_string("ACHTUNG!     ");
            timer0_stop();
        }
        else {
            lcd_string("ALARM!! ACHTUNG!!!!   ");
            timer0_start();
        }

        serial_send_float(voltage, 4, 2);
        serial_send_string(" V");
        serial_send_string("%\r\n");
    }
}