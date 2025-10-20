#define F_CPU 16000000UL                       // Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD -1

#include <avr/io.h>
#include "usart.h"

int main(void)
{
	usart_Init();
	
	while (1)
	{
		usart_sendStringNewLine("Hallo");
	}
}

