#include "WaterLevelController.h"
#include "SoilHumidityController.h"
#include <Wire.h>

//Water level pins
const int trig = 2; //trigger pin
const int echo = 3; 

//Humdity pins
const int humditiyInput = A1;

//I2C configuration
const int slaveAddress = 8;

WaterLevelController waterLevelController(trig, echo);
//SoilHumidityController soilHumidityController(humditiyInput);

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
    //int soilHumidity = soilHumidityController.ReadSoilHumidty();

      uint8_t buffer[2];
  buffer[0] = waterLevel >> 8;
  buffer[1] = waterLevel & 0xff;  
  Wire.write(buffer, 2);
}