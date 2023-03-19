#include <Wire.h>
#include "LEDController.h"

const byte sensorAddress = 8; //I2C address of the sensor controller
const int redLedPin = 2;			// pin for the red LED
const int greenLedPin = 3;			// pin for the green LED
const int yellowLedPin = 4;			// pin for the yellow LED

const int humidityInputPin = A1;	//### Obsolete
const int pumpPin = 10;				//5V pin for the water pump
int pumpCoolDownCycles = 0;


LEDController ledController(redLedPin, greenLedPin, yellowLedPin);


void setup() {
	Serial.begin(9600);
	Wire.begin();

	//Set up pump controller
	pinMode(pumpPin, OUTPUT);
	pinMode(humidityInputPin, INPUT);


}

void loop() {


	char receiveVal = ' ';

	if (Serial.available() > 0)
	{
		receiveVal = Serial.read();
	}

	int waterLevel = readWaterLevel();
	int soilHumidity = analogRead(A1);


	//Serial.print("Water Level:");
	//Serial.println(waterLevel);
	//Serial.print("Humidity Level:");
	//Serial.println(soilHumidity);

	if (receiveVal == '1')
		Serial.print(waterLevel + "#" + soilHumidity);

	if (waterLevel != 0)
		ledController.setWaterLevelLights(waterLevel);
	else
		ledController.flashWarning();

	controlPump(soilHumidity);

	delay(1000);
}

//Read data from I2C slave
int readWaterLevel()
{
	Wire.beginTransmission(sensorAddress);

	int available = Wire.requestFrom(sensorAddress, (uint8_t)2);

	if (available == 2)
	{
		int receivedValue = Wire.read() << 8 | Wire.read();
		return receivedValue;
	}

	Wire.endTransmission();
}

void controlPump(int soilHumidity) {
	//Only trigger pump once the cooldown period is over to give the soil time to properly humidify
	if (soilHumidity < 200 && pumpCoolDownCycles == 0)
	{
		digitalWrite(pumpPin, HIGH);
		delay(5000);
		digitalWrite(pumpPin, LOW);
		pumpCoolDownCycles = 300; // 300 * 1000ms = 5 minutes
	}
	else
		pumpCoolDownCycles--;
}
