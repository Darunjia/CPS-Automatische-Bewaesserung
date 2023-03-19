#pragma once
#ifndef LEDController_h
#define LEDController_h

#include <Arduino.h>

class LEDController {
private:
	int redLedPin;          // pin for the red LED
	int greenLedPin;        // pin for the green LED
	int yellowLedPin;       // pin for the yellow LED
	void lightRed();
	void lightYellow();
	void lightGreen();

public:
	LEDController(int redPin, int greenPin, int yellowPin);
	void setWaterLevelLights(int waterLevel);
	void flashWarning();
};

#endif

