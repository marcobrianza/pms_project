/***************************************************
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to
  interface
 ****************************************************/


#include <Wire.h>
#include "Adafruit_SHT31.h"

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

float temperature = 0;
float humidity = 0;


void sht3x_setup() {
  Serial.println("SHT31 test");
  if (! sht31.begin(0x45)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  Serial.print("Heater Enabled State: ");
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");
}

bool sht3x_loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  bool ret = true;

  if (! isnan(t)) {  // check if 'is not a number'
    temperature = t;
  } else {
    temperature = 0;
    ret = false;
  }

  if (! isnan(h)) {  // check if 'is not a number'
    humidity = h;
  } else {
    humidity = 0;
    ret = false;
  }

  return (ret);
}
