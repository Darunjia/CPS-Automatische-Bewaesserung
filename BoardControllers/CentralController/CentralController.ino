#include <Wire.h>
#include "LEDController.h"

const int waterLevelInputPin = A1;	// pin for serial input (water level)
const int redLedPin = 4;			// pin for the red LED
const int greenLedPin = 3;			// pin for the green LED
const int yellowLedPin = 2;			// pin for the yellow LED

const int humidityInputPin = A2;	//### Obsolete
const int pumpPin = 7;				//5V pin for the water pump
int pumpCoolDownCycles = 0;

LEDController ledController(redLedPin, greenLedPin, yellowLedPin, waterLevelInputPin);


void setup() {
	Serial.begin(9600);

	//Set up pump controller
	pinMode(pumpPin, OUTPUT);
	pinMode(humidityInputPin, INPUT);
}

void loop() {

	char receiveVal = ' ';

	if (Serial.available() > 0)
	{
		receiveVal = Serial.read();		
	}

	int waterLevel = 10; //### read from I2C
	int humidity = 150; //### rad from I2C

	if (receiveVal == '1')
		Serial.print(waterLevel + "#" + humidity);

	if (waterLevel != 0)
		ledController.setWaterLevelLights(waterLevel);
	else
		for (int i = 0; i < 10; i++) //Flash LED Array 10 times in 0.1 second bursts
			ledController.flashWarning(100, 100);

	//Only trigger pump once the cooldown period is over to give the soil time to properly humidify
	if (pumpCoolDownCycles == 0)
		controlPump(humidity);
	else
		pumpCoolDownCycles--;

	//setHumdityLights(humidityLevel);	

	delay(1000);
}


// === Pump Controller ===
//###sanitise humidity values
void controlPump(int humidity)
{
	if (humidity < 200)
	{
		digitalWrite(pumpPin, HIGH);
		delay(5000);
		digitalWrite(pumpPin, LOW);
		pumpCoolDownCycles = 300; // 300 * 1000ms = 5 minutes
	}
}