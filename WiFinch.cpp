/*
 * @file WiFinch.cpp
 * @Authoer RMS (reinerschmidt@roboteurs.com)
 * @date August, 2016
 * @breif A library to drive the PWM servo extestion of the ESP8266 board 
 * 
 * @license
 */

#include <WiFinch.h>
#include <Wire.h>


/*
 * @Breif constructor
 */
WiFinch::WiFinch( ) {

}

/*
 * @Breif begins the servo object, start i2c and init the device
 */
void WiFinch::begin(void) {
 Wire.begin(4,5);
 init();
}

/*
 * @Breif initalizes the onboard IC that will control the servos 
 */
void WiFinch::init(void){
  writeBus(0x40, 0x00, 0x00); //reset 
  delay(10);
  writeBus(0x40, 0x00, 0x10); //enter sleep mode
  writeBus(0x40, 0xfe, 0x87); //set period to 22ms
  delay(10);
  writeBus(0x40, 0x00, 0x20); //exit sleep mode
}

/*
 * @Breif writes an angle to the servo
 */
void WiFinch::writeDegree(char servonum, int angle){
  int dutyCycle = 3960 - angle*2;
  int reg = 0;
  if(servonum <= 7){
      reg = 7 - servonum;      
  }
  if(servonum >= 8){
      reg = 8 + (15 - servonum);     
  }
  
  Wire.beginTransmission(0x40);
  Wire.write((0x06 + reg *4));
  Wire.write((dutyCycle));
  Wire.write((dutyCycle >> 8));
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();

}

/*
 * @Breif writes a half angle to the servo
 */
void WiFinch::writeHalfDegree(char servonum, int angle){
  int dutyCycle = 3960 - angle;
  int reg = 0;
  if(servonum <= 7){
      reg = 7 - servonum;      
  }
  if(servonum >= 8){
      reg = 8 + (15 - servonum);      
  }
  
  Wire.beginTransmission(0x40);
  Wire.write((0x06 + reg *4));
  Wire.write((dutyCycle));
  Wire.write((dutyCycle >> 8));
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();

}

/*
 * @Breif detach servo num
 */
void WiFinch::dettach(char servonum){
  int reg = 0;
  if(servonum <= 7){
      reg = 7 - servonum;      
  }
  if(servonum >= 8){
      reg = servonum - 7;      
  }  
  
  Wire.beginTransmission(0x40);
  Wire.write((0x06 + reg *4));
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();
}

/*
 * @Breif writes a value to the hardware I2C bus
 */
void WiFinch::writeBus(char address, char reg, char data) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}
