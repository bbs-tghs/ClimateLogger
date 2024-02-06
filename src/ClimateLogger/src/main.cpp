#include <Arduino.h>
#include <Wire.h>

#include "ezButton.h"
#include "main.h"

#include "ezButton.h"
#include "main.h"
#include <SPI.h>
#include <Adafruit_BME680.h>

Adafruit_BME680 bme;

void scanner ()
{
  if(bme.endReading()){
    Serial.println(String(bme.temperature) + " " 
                + String(bme.pressure) + " " 
                + String(bme.humidity));
  }
}


void setup() {
  // put your setup code here, to run once:  
  
  Serial.begin(MONITOR_SPEED);
  while(!Serial) {;}
  randomSeed(analogRead(0));
  delay(500);

  pinMode(SW_LOADED, INPUT_PULLUP);
  pinMode(SW_CONFIG, INPUT_PULLUP);
  
  //FTDI232RL-Chip is connected to Serial2
  //This port should be used to communicate with this device
  //So Serial1 can be used for monitoring as usual
  
  Wire.begin (SDA, SCL);   // sda= GPIO_21 /scl= GPIO_22

  bme.begin();
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() {  
  if (Serial.readString() == "print"){
    scanner();
  }
}
