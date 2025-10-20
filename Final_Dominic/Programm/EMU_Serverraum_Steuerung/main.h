/*
 * main.h
 *
 * Created: 14.04.2025 10:50:41
 * Author: Kaufrechner19
 * Beschreibung: Diese .h-Datei enthält alle einzubindenden Dateien und Definitionen für den Preprozessor
 */ 

#pragma once //Inhalt der main.h Datei wird nur einmal kompiliert

// Definition der CPU-Frequenz
#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

// Einbinden der main.h-Dateien
#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "adc.h"
#include "lcd.h"
#include "i2c.h"
#include "UART.h"

#endif /* MAIN_H_ */

// Definitionen der Portpins
#define O2_SENSOR			PA0		//Anschluss an X1:4a
#define TEMP_SENSOR			PA1		//Anschluss an X1:4c
#define LUEFTER_SENSOR		PA2		//Anschluss an X1:5a

#define SCL					PC0		//Anschluss an X1:16c
#define SDA					PC1		//Anschluss an X1:17a

#define TASTER_S1			PD5		//Wechsel Manuell- / Automatikbetrieb
#define TASTER_S2			PD7		//Wechsel Stickstoffventil (geöffnet oder geschlossen)
#define TASTER_S3			PD3		//INT1 
#define TASTER_S4			PD2		//INT0

#define LED_P1				PB0		//LED rot (Anzeige Stickstoff (geöffnet oder geschlossen)
#define LED_P2				PB3		//LED grün
#define LED_P3				PC2		//LED gelb
#define LED_P4				PC3		//LED rot

//Definition der Bereiche anhand Sauerstoffgehalt und Temperatur im Serverraum
#define OPTIMAL				1		//z.B. <15% Sauerstoff
#define TOLERIERT			2		//z.B. 15-17% Sauerstoff
#define BEDROHLICH			3		//z.B. >17% Sauerstoff

//Definition der Zustände der Tür
#define ERLAUBT				1
#define UNTERSAGT			0

//Definition der O2 Schwellwerte
#define O2_OPTIMAL_MAX			15.0
#define O2_TOLERIERT_MIN		15.1
#define O2_TOLERIERT_MAX		17.0
#define O2_BEDROHLICH_MIN		17.1

//Definition der Temperatur Schwellwerte
#define TEMP_OPTIMAL_MAX		15.0
#define TEMP_TOLERIERT_MIN		15.1
#define TEMP_TOLERIERT_MAX		28.0
#define TEMP_BEDROHLICH_MIN		28.1

//Definition des Betriebsmodus
typedef enum {							//Verteilung von konstanten Ganzzahlen an lesbare Namen
	MANUELL,
	AUTOMATIK
} Betriebsmodus;						//Name des Datentyps

extern volatile Betriebsmodus modus;	//Variable "modus" kann außerhalb der main.h verwendet werden

void setup();							//Aufruf bei Programmstart und Initialisierung verschiedener Funktion

uint32_t millis();						//Laufzeitsteuerung

void initExternalInterrupts();			//Initialisiert die Interrupts an den PD2 und PD3

void initTimerInterrupts();				//Initialisiert den 8-Bit Timer und setzt seinen Takt (Prescaler)

void setBetrieb();						//wechselt den aktuellen Betriebsmodus bei Betätigung des Tasters S1

void setLEDs();							//setzt die vorhandenen LEDs auf vordefinierte Fälle

void setFanSpeed();						//setzt die Lüftergeschwindigkeit auf den vorgegebenen Setpoint (Lüftereinstellung)

void updateMeasurements();				//liest alle Sensoren aus und setzt die globalen Variablen auf die aktuellen Werte 

void updateState();						//setzt die Bereiche basierend auf den Sauerstoffwerten

void updateVentil();					//wechselt den Zustand des Stickstoffventils (Automatik mit Case, Manuell mit Taster S2)

void uartOutput();						//Aktualisiert die Ausgabe über UART (z.B. Putty)

void uartOutputTimed();					//sorgt für einen Anzeigen wechsel

static uint8_t adressDAC1 = 103;		//Ansteuerung des Lüfters

float getO2(uint8_t);					//liest analogen Sensorwert aus und wandelt das ADC-Ergebnis in Sauerstoffgehalt in % um

float getTemperature(uint8_t);			//liest analogen Sensorwert aus und wandelt das ADC-Ergebnis in Temperatur in Grad C um

uint16_t getFanSpeed(uint8_t);			//liest analogen Geschwindigkeitswert aus und wandelt das ADC-Ergebnis in U/min um

ISR(TIMER0_OVF_vect);					//Laufzeitsteuerung

ISR(INT0_vect);							//wird ausgelöst wenn Taster S3 gedrückt wird

ISR(INT1_vect);							//wird ausgelöst wenn Taster S4 gedrückt wird
