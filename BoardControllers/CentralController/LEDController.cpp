// === LED CONTROLLER ===
#include "LEDController.h"
#include <Arduino.h>


LEDController::LEDController(int redPin, int greenPin, int yellowPin, int input) {
	redLedPin = redPin;          // pin for the red LED
	greenLedPin = greenPin;        // pin for the green LED
	yellowLedPin = yellowPin;        // pin for the yellow LED

	pinMode(redLedPin, OUTPUT);
	pinMode(greenLedPin, OUTPUT);
	pinMode(yellowLedPin, OUTPUT);
}


void LEDController::setWaterLevelLights(int waterLevel)
{
	Serial.println("Water Level:");
	Serial.println(waterLevel); // debug print

	if (waterLevel < 10)
	{
		lightRed();
	}
	else if (waterLevel > 10 && waterLevel < 30)
	{
		lightYellow();
	}
	else
	{
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

void LEDController::flashWarning(int uptime_ms, int downtime_ms) {
	digitalWrite(redLedPin, HIGH);
	digitalWrite(yellowLedPin, HIGH);
	digitalWrite(greenLedPin, HIGH);

	delay(uptime_ms);

	digitalWrite(redLedPin, HIGH);
	digitalWrite(yellowLedPin, HIGH);
	digitalWrite(greenLedPin, HIGH);

	delay(downtime_ms);

}