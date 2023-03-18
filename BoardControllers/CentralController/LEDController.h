#pragma once
#ifndef LEDController_h
#define LEDController_h

#include <Arduino.h>

class LEDController {
private:
	int inputPin;			// pin for the I2C 
	int redLedPin;          // pin for the red LED
	int greenLedPin;        // pin for the green LED
	int yellowLedPin;       // pin for the yellow LED
	void lightRed();
	void lightYellow();
	void lightGreen();

public:
	LEDController(int redPin, int greenPin, int yellowPin, int input);
	void setWaterLevelLights(int waterLevel);
	void flashWarning(int uptime_ms, int downtime_ms);
};

#endif

