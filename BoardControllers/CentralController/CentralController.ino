#include <Wire.h>
#include "LEDController.h"

const int waterLevelInputPin = A1;	// pin for serial input (water level)
const int redLedPin = 4;			// pin for the red LED
const int greenLedPin = 3;			// pin for the green LED
const int yellowLedPin = 2;			// pin for the yellow LED

const int humidityInputPin = A2;	//### Obsolete
const int pumpPin = 7;				//5V pin for the water pump

LEDController ledController(redLedPin, greenLedPin, yellowLedPin, waterLevelInputPin);


void setup() {
	Serial.begin(9600);

	//Set up pump controller
	pinMode(pumpPin, OUTPUT);
	pinMode(humidityInputPin, INPUT);
}

void loop() {

	controlPump();
	int waterLevel = 10; //### read from I2C
	if (waterLevel != 0)
		ledController.setWaterLevelLights(waterLevel);
	else
		for (int i = 0; i < 10; i++) //Flash LED Array 10 times in 0.1 second bursts
			ledController.flashWarning(100, 100);

	//setHumdityLights(humidityLevel);	

	delay(300000);
}

// === Pump Controller ===
//###sanitise humidity values
void controlPump()
{
	int humidity = 150; //### rad from I2C
	Serial.println("Humidity: " + humidity); // debug print

	if (humidity < 200)
	{
		digitalWrite(pumpPin, HIGH);
		delay(5000);
		digitalWrite(pumpPin, LOW);
	}
}