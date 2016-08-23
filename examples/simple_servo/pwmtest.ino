/******************************************************************************
 * @Breif This program moves a servo back and forth. Like Blinky but with a servo 
 * 
 * 

 * 
 */****************************************************************************

#include "Wire.h"
#include "WiFinch.h"

WiFinch servo = WiFinch();

/* setup the servo */
void setup() {
  servo.begin();
}



void loop() {
    //move servo 0 to 45 degrees
    servo.writeDegree(0, 45);
    delay(1000);
    
    //move servo 0 to 135 degrees
    servo.writeDegree(0, 135); 
    delay(1000);
}
