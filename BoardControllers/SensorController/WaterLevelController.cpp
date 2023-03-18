
#include "WaterLevelController.h"
#include <Arduino.h>

WaterLevelController::WaterLevelController(int trig, int echo)
{
	trigPin = trig; // TRIG 
	echoPin = echo;  // ECHO 

	pinMode(trigPin, OUTPUT); // Config trigger pin to output mode
	pinMode(echoPin, INPUT);  // Config echo pin to input mode
}

int WaterLevelController::ReadWaterLevel() {
    // Generate 10-microsecond pulse to TRIG pin
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure duration of pulse from ECHO pin
    duration_us = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distance_cm = 0.017 * duration_us;

    int send = distance_cm;
    Serial.println(send); //debug print

    return send;
}
