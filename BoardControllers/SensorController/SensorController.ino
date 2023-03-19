#include "WaterLevelController.h"
#include "SoilHumidityController.h"
#include <Wire.h>

//Water level pins
const int trig = 1; //trigger pin
const int echo = 2; 

//Humdity pins
const int humditiyInput = A1;

//I2C configuration
const int slaveAddress = 8;

WaterLevelController waterLevelController(trig, echo);
SoilHumidityController soilHumidityController(humditiyInput);

void setup()
{
    Serial.begin(9600);
    Wire.begin(slaveAddress);
    Wire.onRequest(requestEvent);
}

void loop()
{
    delay(100);
}

void requestEvent() {

    int waterLevel = waterLevelController.ReadWaterLevel();
    int soilHumidity = soilHumidityController.ReadSoilHumidty();
    int sensorValues[2];
    sensorValues[0] = waterLevel;
    sensorValues[1] = soilHumidity;

    Wire.write((uint8_t*)sensorValues, 2 * sizeof(int)); // Send the array
}