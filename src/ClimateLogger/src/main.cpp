#include <Arduino.h>
#include <Wire.h>

#include "ezButton.h"
#include "main.h"
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BME680.h>
#include <Adafruit_CCS811.h>

ezButton btnStable(SW_STABLE);         //Pin Schalter Stable | not stable
ezButton btnNoise(SW_NOISE);           //Pin Schalter mit | ohne Noise
ezButton btnLoaded(SW_LOADED, INPUT);  //Pin Schalter normal belastet | kleine Last (1%) | entlastet
ezButton btnPrint(SW_PRINT);           //Pin für Taster Print
ezButton btnSpeed(SW_SPEED);           //Pin für Taster Reserve


boolean bLED_STABLE  = LED_OFF;        //act. state of the Leds inside the pushbuttons
boolean bED_NOISE    = LED_OFF;
boolean bED_LOADED   = LED_OFF;
boolean bED_PRINT    = LED_OFF;
boolean bED_SPEED    = LED_OFF;



void scanner ()
{
  Serial.println();
  Serial.println("I2C scanner. Scanning ...");
  byte count = 0;

  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission(i);          // Begin I2C transmission Address (i)
    if (Wire.endTransmission() == 0)  // Receive 0 = success (ACK response) 
    {
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX);     // PCF8574 7 bit address
      Serial.println(")");
      count++;
    }
  }
  Serial.print("Found ");      
  Serial.print(count, DEC);        // numbers of devices
  Serial.println(" device(s).");
}


void setup() {
  // put your setup code here, to run once:

  Serial.begin (115200);  
  
  Serial.begin( MONITOR_SPEED );
  while ( !Serial ) {;}
  randomSeed( analogRead(0) );
  delay(500);

  pinMode( LED_STABLE, OUTPUT );
  pinMode( LED_NOISE,  OUTPUT );
  pinMode( LED_LOADED, OUTPUT );
  pinMode( LED_PRINT,  OUTPUT );
  pinMode( LED_SPEED,  OUTPUT );

  digitalWrite( LED_STABLE, bLED_STABLE );
  digitalWrite( LED_NOISE,  bED_NOISE );
  digitalWrite( LED_LOADED, bED_LOADED );
  digitalWrite( LED_PRINT,  bED_PRINT );
  digitalWrite( LED_SPEED,  bED_SPEED );

  pinMode( SW_LOADED, INPUT_PULLUP );
  pinMode( SW_CONFIG, INPUT_PULLUP );
  
  //FTDI232RL-Chip is connected to Serial2
  //This port should be used to communicate with this device
  //So Serial1 can be used for monitoring as usual
  Serial2.begin( SERIAL2_BAUD, SERIAL2_PROTOCOL, RXD2, TXD2);
  Serial2.setTimeout( SERIAL2_TIMEOUT );

  
  
  Wire.begin ( SDA, SCL );   // sda= GPIO_21 /scl= GPIO_22






}

void loop() {
  // put your main code here, to run repeatedly:


  btnStable.loop();   //call die methods regularly to keep the buttons work
  btnNoise.loop();
  btnLoaded.loop();
  btnPrint.loop();
  btnSpeed.loop();

  //this is how the buttons can be used...
  if (btnStable.isPressed() ) {
    bLED_STABLE = !bLED_STABLE;
    digitalWrite( LED_STABLE, bLED_STABLE );

  }

  if (btnNoise.isPressed() ) {
    bED_NOISE = !bED_NOISE;
    digitalWrite( LED_NOISE,  bED_NOISE );
  }

  if (btnLoaded.isPressed() ) {
    bED_LOADED = !bED_LOADED;
    digitalWrite( LED_LOADED, bED_LOADED );

  }
  


  Scanner ();
  delay (500);


}

