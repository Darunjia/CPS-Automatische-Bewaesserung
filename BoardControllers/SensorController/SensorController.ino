#include "WaterLevelController.h"
#include "SoilHumidityController.h"
#include <Wire.h>


void setup()
{
    Serial.begin(9600);
    Wire.begin(22);
    Wire.onRequest(requestEvent);
}

void loop()
{
}

void requestEvent() {
    union
    {
        int sensorValues[2];
        byte buf[6];
    } sensorValueUnion;



    Wire.write((byte*)&sensorValueUnion, sizeof sensorValueUnion);
}