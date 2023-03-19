#include "SoilHumidityController.h"
#include <Arduino.h>

SoilHumidityController::SoilHumidityController(int input) {
	inputPin = input;			// pin for serial input (water level)

	pinMode(inputPin, INPUT);
}



int SoilHumidityController::ReadSoilHumidty()
{
	int sensorValue = analogRead(inputPin);

	Serial.println("Soil Humidity: " + sensorValue); //debug

	return sensorValue;
}

