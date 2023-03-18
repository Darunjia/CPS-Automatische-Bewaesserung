// SoilHumidityController.h

#ifndef _SOILHUMIDITYCONTROLLER_h
#define _SOILHUMIDITYCONTROLLER_h

#include "arduino.h"

class SoilHumidityController {
private:
	int inputPin;	// pin for the Analog Read

public:
	SoilHumidityController(int input);
	int  ReadSoilHumidty();

};

#endif

