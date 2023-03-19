#include <Wire.h>
#include "LEDController.h"

const int sensorAddress = 8; //I2C address of the sensor controller

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
	Wire.begin();

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

	int *sensorValues = readSensors();

	//unfold array for easier readability
	int waterLevel = sensorValues[0];
	int soilHumidity = sensorValues[1];

	if (receiveVal == '1')
		Serial.print(waterLevel + "#" + soilHumidity);

	if (waterLevel != 0)
		ledController.setWaterLevelLights(waterLevel);
	else
		for (int i = 0; i < 10; i++) //Flash LED Array 10 times in 0.1 second bursts
			ledController.flashWarning(100, 100);

	//Only trigger pump once the cooldown period is over to give the soil time to properly humidify
	if (pumpCoolDownCycles == 0)
		controlPump(soilHumidity);
	else
		pumpCoolDownCycles--;

	//setHumdityLights(humidityLevel);	

	delay(1000);
}

int * readSensors()
{
	int arrayToReceive[2];
	const int arrayLength = 2; //Define constant for easier expandability

	Wire.requestFrom(sensorAddress, arrayLength * sizeof(int)); // Request the array
	while (Wire.available() < arrayLength * sizeof(int)); // Wait until the data is available
	Wire.readBytes((uint8_t*)arrayToReceive, arrayLength * sizeof(int)); // Read the data into the array

	return arrayToReceive;	
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