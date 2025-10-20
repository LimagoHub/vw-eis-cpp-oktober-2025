#ifndef SERIAL_H_
#define SERIAL_H_

#define F_CPU 16000000UL //Takt
#include <avr/io.h>
#define BAUD 9600 //Einstellung der Baudrate
#define MYUBRR ((F_CPU/(16UL*BAUD))-1) //Berechnung des Formelwert für das Register

void serial_init();
uint8_t serial_get_byte();
void serial_send_byte(uint8_t byteToSend);
void serial_send_string(uint8_t * stringToSend);
void serial_send_int(uint16_t * integerToSend);
void serial_send_float(float number, int width, int precision);

#endif /* SERIAL_H_ */