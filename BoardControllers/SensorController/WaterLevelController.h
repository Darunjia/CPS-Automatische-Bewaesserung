// WaterLevelController.h

#ifndef _WATERLEVELCONTROLLER_h
#define _WATERLEVELCONTROLLER_h

#include "arduino.h"

class WaterLevelController {
private:
	int trigPin; // TRIG 
	int echoPin;  // ECHO 

	//us == microseconds
	float duration_us, distance_cm;
public:
	WaterLevelController(int trig, int echo);
	int ReadWaterLevel();
};

#endif

