//////////////////////////////////////////////////////////////////////////////////////
// Name        : adc.c
// Beschreibung : Diese .c-Datei enthält Funktionen für die Benutzung des ADC-
//                Wandlers (Analog-Digital-Converter)
// Quelle       : Eigene Implementierung basierend auf Atmel AVR-Dokumentation
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// Einbinden des ADC-Headers
//////////////////////////////////////////////////////////////////////////////////////
#define F_CPU 16000000UL
#include "adc.h"
#include <util/delay.h>

//////////////////////////////////////////////////////////////////////////////////////
// Name        : ADC_Init
// Beschreibung : Initialisiert den ADC mit AVcc als Referenzspannung und Prescaler 128
// Parameter    : -
// Return       : -
//////////////////////////////////////////////////////////////////////////////////////
void ADC_Init()
{
	DDRA = 0x00; // Alle A-Pins als Eingang
	ADCSRA = (1 << ADEN); // ADC aktivieren
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
	ADMUX = (1 << REFS0); // AVcc als Referenzspannung, Kanal 0 als Standard
}

//////////////////////////////////////////////////////////////////////////////////////
// Name        : ADC_Read
// Beschreibung : Liest den ADC-Wert eines angegebenen Kanals
// Parameter    : uint8_t channel - ADC-Kanal (0–7)
// Return       : uint16_t - digitaler Messwert (0–1023)
//////////////////////////////////////////////////////////////////////////////////////
uint16_t ADC_Read(uint8_t channel)
{
	ADMUX &= 0xF0; // Kanalbits löschen
	ADMUX |= (channel & 0x0F); // Neuen Kanal setzen

	ADCSRA |= (1 << ADSC); // Wandlung starten
	while ((ADCSRA & (1 << ADIF)) == 0); // Warten auf Ende

	_delay_us(10); // Kleine Pause für Stabilität

	uint16_t result = ADCL;
	result |= (ADCH << 8); // Ergebnis zusammensetzen

	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name        : ADC_ReadAvgFloat
// Beschreibung : Gibt den Mittelwert von 32 Messungen eines Kanals als Float zurück
// Parameter    : uint8_t channel - ADC-Kanal (0–7)
// Return       : float - gemittelter Wert
//////////////////////////////////////////////////////////////////////////////////////
float ADC_ReadAvgFloat(uint8_t channel)
{
	uint32_t sum = 0;

	for (uint8_t i = 0; i < 32; i++)
	{
		sum += ADC_Read(channel);
		_delay_ms(1); // Signal beruhigen
	}

	float average = (float)sum / 32.0;
	return average;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name        : ADC_ReadAvgInt
// Beschreibung : Gibt den Mittelwert von 32 Messungen eines Kanals als Integer zurück
// Parameter    : uint8_t channel - ADC-Kanal (0–7)
// Return       : uint8_t - gemittelter Wert (ganzzahlig)
//////////////////////////////////////////////////////////////////////////////////////
uint8_t ADC_ReadAvgInt(uint8_t channel)
{
	uint16_t sum = 0;

	for (uint8_t i = 0; i < 32; i++)
	{
		sum += ADC_Read(channel);
		_delay_ms(1);
	}

	return (uint8_t)(sum / 32);
}
