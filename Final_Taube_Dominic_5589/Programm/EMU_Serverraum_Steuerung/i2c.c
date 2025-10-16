//////////////////////////////////////////////////////////////////////////////////////
// Name		: i2c.c
// Beschreibung : Diese .c-Datei enthält Funktionen für die Benutzung der i2c-
//		  Schnittstelle
// Quelle	: https://www.mikrocontroller.net/articles/AVR_TWI
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
//Einbinden des i2c-Headers
//////////////////////////////////////////////////////////////////////////////////////
#include "i2c.h"

//////////////////////////////////////////////////////////////////////////////////////
// Name		: i2c_init
// Beschreibung : Initialisiert die I2C-Schnittstelle
// Parameter	: -
// Return	: -
//////////////////////////////////////////////////////////////////////////////////////
void i2c_init(void)
{
	TWSR = 0;
	TWBR = ((F_CPU/F_SCL)-16)/2;		//Taktfrequenz von SCL
}

//////////////////////////////////////////////////////////////////////////////////////
// Name		: sendData
// Beschreibung : Sendet Daten über die I2C-Schnittstelle
// Parameter	: uint8_t address; Addresse des Slaves
//				  uint16_t data; Datenpaket das übertragen werden soll
// Return	: -
//////////////////////////////////////////////////////////////////////////////////////

void mcp4725_sendFast(uint8_t adressDAC1, uint16_t value)
{
	adressDAC1 = adressDAC1 << 1;  // 7-Bit ? 8-Bit

	uint8_t high = (value >> 4) & 0xFF;
	uint8_t low  = (value & 0x0F) << 4;

	// START
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	// SLA+W
	TWDR = adressDAC1;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	// FAST MODE-Kommando
	TWDR = 0x40;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	// HIGH Byte
	TWDR = high;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	// LOW Byte
	TWDR = low;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));

	// STOP
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

