/*
 * TMP102.cpp - Interface a TMP thermometer to an AVR via i2c
 * Version 1.5
 * Copyright (c) 2016 KonstantinDimitrov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "TMP102.h"
#include <Arduino.h>  
#include <Wire.h>     // I2C library

int tmp102Address = 0x48;/* This is the I2C address for our chip.
This value is correct if you tie the ADD0 pin to ground. See the datasheet for some other values. */


TMP::TMP()
{
}

void TMP::init()
{
	Wire.begin(); //Initiate the Wire library and join the I2C bus as a master	
}

// This can be called at 100ms intervals to get new data
void TMP::getTemperature(int *t)
{

  unsigned int complement;// = 0xe70 - 1
  float getTemperature;
  
  Wire.requestFrom(tmp102Address, 2); //reads data from the sensor

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4;

  /*
   
   Serial.println();
   Serial.print("complement1 = 0x");
   Serial.println(complement,HEX);
   
   complement ^= 0xfff;
   
   Serial.println();
   Serial.print("complement2 = 0x");
   Serial.println(complement,HEX);
   */

  if(TemperatureSum&0x800)//negative temperature
  {
    complement = TemperatureSum - 1;
    complement ^= 0xfff;
	getTemperature = complement * 0.0625 * (-1);
  }
  else
  {
	  getTemperature = TemperatureSum * 0.0625;
  }
  //correctedtemp = convertedtemp - 5; 

 
   *t=   (int)getTemperature;
}

// Set the default object
TMP TMP102 = TMP();

                               /*END OF FILE*/
