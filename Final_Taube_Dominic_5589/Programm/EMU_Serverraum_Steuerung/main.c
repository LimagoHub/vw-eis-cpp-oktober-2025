/*
 * EMU_Serverraum_Steuerung.c
 *
 * Created: 14.04.2025 07:38:58
 * Author : Kaufrechner19
 */ 

#include "main.h"									//Einbinden der main.h

//Deklarieren globaler Variablen
volatile uint32_t _millis = 0;
float temperatur;
float o2;
uint8_t state = 0;
uint16_t fanSpeed;									//Lüfter Ist-Drehzahl
uint16_t fanSpeedSetpoint = 0;						//Lüfter Soll-Drehzahl
uint16_t dacValue = 1;								//Steuert die Lüftergeschwindigkeit 
uint8_t tuerKontakt = 0;
uint8_t tempState = 0;
uint8_t tuerZugang = 0;
uint8_t alarm = 0;

volatile Betriebsmodus modus = AUTOMATIK;			//Variable modus mit Datentyp Betriebsmodus / Standardwert: AUTOMATIK
 

///////////////////////////////MAIN//////////////////////////////////////

int main(void)
{
	setup();										//Initialisierung aller Module, Timer, Interrupts, Ein- und Ausgänge
	
	uint32_t startTime = millis();					//Start der Laufzeit
	uint8_t setupDone = 0;							//Statusvariable
	
	lcd_string("EMU Serverraum");					// Erste Zeile
	lcd_command(FORCE_SND_LINE);					// Cursor auf zweite Zeile setzen
	lcd_string("Steuerung_V2");						// Zweite Zeile
	
    while (1) 
    {	
		if (!setupDone && millis() - startTime >= 5000)	//Überprüfen, ob das Setup schon durchgeführt wurde
		{
			lcd_command(CLEAR);
			lcd_command(0x08); // Display ausschalten
			setupDone = 1;
		}
		if (setupDone){									//Nach Startvorgang, Dauerschleife
			updateMeasurements();
			updateState();
			setLEDs();
			setBetrieb();	
			mcp4725_sendFast(adressDAC1, dacValue);		//Ansteuerung des Lüfters über I2C
			setFanSpeed();								
			uartOutputTimed();							
		}

    }
}

//////////////////////////////////////////////////////////////////////////

void setup(){
	//Initialisieren der Module
	i2c_init();
	lcd_init();
	ADC_Init();
	UART_init();
	
	//Interrupts initialisieren und aktivieren
	initExternalInterrupts();
	initTimerInterrupts();
	DDRC &= ~((1 << PC0) | (1 << PC1));
	PORTC |= (1 << PC0) | (1 << PC1);			//PullUp Widerstand auf I2C-Leitung
	DDRB |= (1 << LED_P1) | (1 << LED_P2);		//LED Pins auf Output setzen
	DDRC |= (1 << LED_P3) | (1 << LED_P4);
	
	//Variablen mit Messwerte füllen
	temperatur = getTemperature(TEMP_SENSOR);
	o2 = getO2(O2_SENSOR);
	fanSpeed = getFanSpeed(LUEFTER_SENSOR);
	
	// Alle Taster als Eingang mit PullUp aktivieren
	DDRD &= ~((1 << TASTER_S1) | (1 << TASTER_S2) | (1 << TASTER_S3) | (1 << TASTER_S4));
	PORTD |= (1 << TASTER_S1) | (1 << TASTER_S2) | (1 << TASTER_S3) | (1 << TASTER_S4);
	
}

//nicht blockierende Laufzeitsteuerung
uint32_t millis(){		
	uint32_t ms;
	cli();				//Interrupts aus, um sicheren Zugriff zu ermöglichen
	ms = _millis;		//Milisekundenwert speichern
	sei();				//Set Enable Interrupts
	return ms;			//Zeit in ms zurückgeben
}

void initExternalInterrupts(){
	GICR |= (1 << INT0) | (1 << INT1); // Externe Interrupts INT0 & INT1 aktivieren
	MCUCR |= (1 << ISC11);             // INT1 bei fallender Flanke
	MCUCR |= (1 << ISC01);             // INT0 bei fallender Flanke
}

void initTimerInterrupts(){
	TCCR0 = (1 << CS01) | (1 << CS00);	// Prescaler 64
	TIMSK |= (1 << TOIE0);				// Overflow-Interrupt an
}

void setBetrieb() {
	//Status- und Entprellvariablen deklarieren und initialisieren
	static uint8_t lastStableState = 1;
	static uint8_t lastReadState = 1;
	static uint32_t lastDebounceTime = 0;

	uint8_t currentRead = PIND & (1 << TASTER_S1);	//currentRead auf aktuellen Tasterstatus setzen

	if (currentRead != lastReadState) {
		lastDebounceTime = millis();				// potenzieller Wechsel erkannt
	}

	// Entprellzeit prüfen
	if ((millis() - lastDebounceTime) > 50) {
		if (currentRead != lastStableState) {
			lastStableState = currentRead;

			if (lastStableState == 0) {				// Taster gedrückt (fallende Flanke)
				// Modus umschalten
				if (modus == MANUELL) {
					modus = AUTOMATIK;
				} else
					{
					modus = MANUELL;
					}
			}
		}
	}
	
	lastReadState = currentRead;					// Status für nächsten Vergleich speichern
}

void setLEDs(){
	//setze alle vorhandenen LEDs auf definierte Fälle
	if (alarm == 0)
	{
		updateVentil();	//überprüfe und ggf. wechsele Zustand des Stickstoffventils
	}
	
	if (tuerZugang == 1)
	{
		PORTB |= (1<<LED_P2);
		PORTC &= ~(1<<LED_P4);
	}
	else if (tuerZugang == 0)
	{
		PORTB &= ~(1<<LED_P2);
		PORTC |= (1<<LED_P4);
	}
}

void setFanSpeed(){
	float fanstep = 4095.0 / 1350.0;	// Umrechnungsfaktor: RPM ? DAC-Wert
	// Nur aktualisieren, wenn Ist-Wert ungleich Soll-Wert
	if (fanSpeed < fanSpeedSetpoint || fanSpeed > fanSpeedSetpoint) {
		dacValue = (uint16_t)(fanSpeedSetpoint * fanstep + 0.5f);  // Berechnen und aufrunden
	}
	// DAC-Wert begrenzen
	if (dacValue >= 4096) {
		dacValue = 4095;
		} else if (dacValue <= 0) {
		dacValue = 0;
	}
}

void updateMeasurements(){
	temperatur = getTemperature(TEMP_SENSOR);		//lies den Temperatursensor aus und speichere ihn in der globalen Variable
	o2 = getO2(O2_SENSOR);							//lies den Sauerstoffsensor aus und speichere ihn in der globalen Variable
	fanSpeed = getFanSpeed(LUEFTER_SENSOR);			//lies die Lüftergeschwindigkeit aus und speichere ihn in der globalen Variable
}

void updateState() {
	if (o2 >= 0 && o2 <= O2_OPTIMAL_MAX) {							//Ist der Sauerstoffgehalt zwischen 0 und 15 %?
		state = OPTIMAL;											//Stelle Anlagenstatus auf OPTIMAL
	}
	else if (o2 >= O2_TOLERIERT_MIN && o2 <= O2_TOLERIERT_MAX) {	//Ist der Sauerstoffgehalt zwischen 15 und 17 %?
		state = TOLERIERT;											//Stelle Anlagenstatus auf TOLERIERT
	}
	else if (o2 >= O2_BEDROHLICH_MIN && o2 <= 100) {				//Ist der Sauerstoffgehalt zwischen 17 und 100 %?
		state = BEDROHLICH;											//Stelle Anlagenstatus auf BEDROHLICH							
	}
	//Temperatur und Lüfter
	if (temperatur < TEMP_OPTIMAL_MAX)
	{
		tempState = OPTIMAL;
		fanSpeedSetpoint = 300;
	} 
	else if (temperatur >= TEMP_TOLERIERT_MIN && temperatur <= TEMP_TOLERIERT_MAX)
	{
		tempState = TOLERIERT;
		fanSpeedSetpoint = 700;
	}
	else if (temperatur >= TEMP_BEDROHLICH_MIN)
	{
		tempState = BEDROHLICH;
		fanSpeedSetpoint = 1000;
	}
	//Türzugang
	if (o2 <= O2_TOLERIERT_MAX || (PORTB &= (1 << LED_P1)))
	{
		tuerZugang = UNTERSAGT;
	} 
	else
	{
		tuerZugang = ERLAUBT;
	}
	//Alarm
	if (tuerKontakt == 1 && tuerZugang == 0)
	{
		alarm = 1;
		PORTB &= ~(1 << LED_P1);		// Ventil zu
	}
	else
	{
		alarm = 0;
	}
}

void updateVentil() {
	//Status- und Umschaltvariablen deklarieren und initialisieren
	static uint8_t lastState = 1;
	static uint32_t lastToggleTime = 0;
	uint8_t currentState;

	//Überprüfe ob der Taster S2 gedrückt wurde
	if (PIND & (1 << TASTER_S2)) {
		currentState = 1;  // Taster ist NICHT gedrückt (HIGH)
		} else {
		currentState = 0;  // Taster ist gedrückt (LOW)
	}
	
	//Überprüfe ob das Stickstoffventil im Manuell oder Automatik geändert wird
	if (modus == MANUELL) {
		if (lastState == 1 && currentState == 0) {
			if (millis() - lastToggleTime >= 200)
				{
				// Fallende Flanke ? Taster gedrückt
				PORTB ^= (1 << LED_P1);  // Toggle Ventil-LED
				lastToggleTime = millis();
				}	
			}
		} else if (modus == AUTOMATIK) {	// Stickstoffventil anhand Anlagenstatus im  Automatikmodus umstellen
		switch (state) {
			case OPTIMAL:
			PORTB &= ~(1 << LED_P1);		// Ventil zu
			break;
			case TOLERIERT:
			PORTB &= ~(1 << LED_P1);		// Ventil zu
			break;
			case BEDROHLICH:
			PORTB |= (1 << LED_P1);			// Ventil auf
			break;
		}
	}
}

//alle 2s soll die UART-Ausgabe aktualisiert werden
void uartOutputTimed(){
	static uint32_t lastUartTime = 0;
	uint32_t now = millis();
	
	if (now - lastUartTime >= 2000)
	{
		uartOutput();
		lastUartTime = now;
	}
	
}

void uartOutput(void) {
	char temp[15];	//Zeichen-Array für Umwandelung von Zahlen in String

	// ANSI Escape: Cursor 10 Zeilen hoch und Zeile löschen
	// (10, weil wir 10 Zeilen Inhalt haben)
	UART_send_string("\033[10A");  // Cursor 10 Zeilen hoch
	UART_send_string("\033[J");   // Inhalt ab hier löschen

	// Trennlinie oben für eine klare Trennung
	UART_send_string("----------------------\n\r");

	//Sauerstoffgehaltsbereich
	UART_send_string("Sauerstoffgehalt: ");
	if (state == OPTIMAL) {
		UART_send_string("< 15 %\n\r");
		} else if (state == TOLERIERT) {
		UART_send_string("15 % bis 17 %\n\r");
		} else if (state == BEDROHLICH) {
		UART_send_string("> 17 %\n\r");
	}

	// Temperaturbereich
	UART_send_string("Temperatur: ");
	if (temperatur < TEMP_OPTIMAL_MAX) {
		UART_send_string("< 15 Grad\n\r");
		} else if (temperatur >= TEMP_TOLERIERT_MIN && temperatur <= TEMP_TOLERIERT_MAX) {
		UART_send_string("15 Grad bis 28 Grad\n\r");
		} else if (temperatur >= TEMP_BEDROHLICH_MIN) {
		UART_send_string("> 28 Grad\n\r");
	}

	// Lüftergeschwindigkeit
	UART_send_string("Luefter: ");
	dtostrf(fanSpeed, 3, 0, temp);
	UART_send_string(temp);
	UART_send_string(" U/min\n\r");

	// Modus
	UART_send_string("Modus: ");
	if (modus == MANUELL) {
		UART_send_string("MANUELL\n\r");
		} else {
		UART_send_string("AUTOMATIK\n\r");
	}

	// Ventilstatus (LED_P1 gibt den Zustand an)
	UART_send_string("Stickstoffventil: ");
	if (PORTB & (1 << LED_P1)) {
		UART_send_string("AUF\n\r");
		} else {
		UART_send_string("ZU\n\r");
	}
	
	// Türzugang
	UART_send_string("Tuerzugang: ");
	if (tuerZugang == 1) {
		UART_send_string("erlaubt\n\r");
		} else {
		UART_send_string("untersagt\n\r");
	}
	
	// Türstatus 
	UART_send_string("Tuerstatus: ");
	if (tuerKontakt == 1) {
		UART_send_string("AUF\n\r");
		} else {
		UART_send_string("ZU\n\r");
	}
	
	// Alarmstatus
	if (alarm == 1) 
	{
		// Platzhalter
		UART_send_string("\n");
		UART_send_string("Alarm: Tuer unerlaubt geoeffnet!\n\r");
	}

	// Abschluss-Trennlinie
	UART_send_string("----------------------\r");
}

float getO2(uint8_t sensor){
	float o2_step = 100.0 / 1023.0;						//Maximaler Sauerstoffwert aufgeteilt auf 10 Bit ADC
	float sauerstoff = ADC_ReadAvgFloat(sensor);		//Durchschnittswert aus 32 Sensorwerten auslesen und in o2 speichern
	return (sauerstoff * o2_step);						//Sensorwert * Sauerstoffschritt zurückgeben = aktueller Sauerstoffgehalt
}

float getTemperature(uint8_t sensor){
	float temp_step = 100.0 / 1023.0;					//Maximaler Temperaturwert aufgeteilt auf 10 Bit ADC
	float temp = ADC_ReadAvgFloat(sensor);				//Durchschnittswert aus 32 Sensorwerten auslesen und in temp speichern
	return (temp * temp_step);							//Sensorwert * Temperaturwert zurückgeben = aktueller Temperaturwert
}

uint16_t getFanSpeed(uint8_t sensor) {
	float fan_step = 1350.0f / 1023.0f;					// Umrechnungsfaktor: ADC-Wert (0–1023) in RPM (0–1350)
	uint16_t adc = ADC_Read(sensor);					// ADC-Wert vom Sensor einlesen
	uint16_t result = adc * fan_step;					// Umrechnen in Drehzahl (RPM)

	//Rückgabe der berechneten Drehzahl
	return result;
}

//Millis-Funktion hochzählen
ISR(TIMER0_OVF_vect){
	_millis++;
}

ISR(INT1_vect)
{
	tuerKontakt = (tuerKontakt == 0) ? 1:0;
}

ISR(INT0_vect)
{
}
