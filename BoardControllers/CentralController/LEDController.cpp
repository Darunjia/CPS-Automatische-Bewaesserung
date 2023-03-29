// === LED CONTROLLER ===
#include "LEDController.h"
#include <Arduino.h>


LEDController::LEDController(int redPin, int greenPin, int yellowPin) {
	redLedPin = redPin;          // pin for the red LED
	greenLedPin = greenPin;        // pin for the green LED
	yellowLedPin = yellowPin;        // pin for the yellow LED

	pinMode(redLedPin, OUTPUT);
	pinMode(greenLedPin, OUTPUT);
	pinMode(yellowLedPin, OUTPUT);
}


void LEDController::setWaterLevelLights(int waterLevel)
{
	//Serial.println("Water Level: " + waterLevel);

	if (waterLevel > 12)
	{
    //Serial.println("lighting red");
		lightRed();
	}
	else if (waterLevel <= 12 && waterLevel >= 5)
	{
    //Serial.println("lighting yellow");
		lightYellow();
	}
	else if (waterLevel < 5)
	{
    //Serial.println("lighting green");
		lightGreen();
	}
}

void LEDController::lightRed()
{
	digitalWrite(redLedPin, HIGH);
	digitalWrite(yellowLedPin, LOW);
	digitalWrite(greenLedPin, LOW);
}

void LEDController::lightYellow()
{
	digitalWrite(redLedPin, LOW);
	digitalWrite(yellowLedPin, HIGH);
	digitalWrite(greenLedPin, LOW);
}

void LEDController::lightGreen() {
	digitalWrite(redLedPin, LOW);
	digitalWrite(yellowLedPin, LOW);
	digitalWrite(greenLedPin, HIGH);
}

void LEDController::flashWarning() {
	digitalWrite(redLedPin, HIGH);
	digitalWrite(yellowLedPin, HIGH);
	digitalWrite(greenLedPin, HIGH);

	delay(1000);

	digitalWrite(redLedPin, HIGH);
	digitalWrite(yellowLedPin, HIGH);
	digitalWrite(greenLedPin, HIGH);

	delay(1000);

}