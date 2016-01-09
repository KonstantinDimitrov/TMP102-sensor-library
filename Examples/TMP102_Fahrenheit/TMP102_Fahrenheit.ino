#include <Wire.h>   //Wire library for I2C communication
#include <TMP102.h> //TMP102 sensor library

void setup()
{
  Serial.begin(9600); //Starts serial communication at speed 9600
  TMP102.init();      //Starts reading from the sensor
}

void loop()
{
  int t;
  delay(100);  // There will be new values every 100ms
  TMP102.getTemperature(&t);  //gets temperature value in Celsius
  Serial.print("Temperature: "); // Pirints the data in the serial monitor
  Serial.println((t * 9) / 5 + 32); //Turn Celsius in Fahrenheit
}
