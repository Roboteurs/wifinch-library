/******************************************************************************
 * @Breif This program will sweep all 16 servos back and forth over 180 degrees. 
 * Then it will detach the servos
 * 
 * Servos are attached automatically by writing an angle to them 
 * 
 */****************************************************************************


#include "WiFinch.h"

WiFinch servo = WiFinch();

/* setup the servo */
void setup() {
  servo.begin();
  servo.attach(0);
}
int pos = 0;


void loop() {
  /* move all the servos from 0 to 180 degrees */
  for (pos = 0; pos <= 180; pos += 1) { 
    // in steps of 1 degree
    for(int i = 0; i < 16; i++){
    servo.writeDegree(i, pos);             
    delay(1);                      
    }
  }
  
  /* move all the servos from 180 to 0 degrees */
  for (pos = 180; pos >= 0; pos -= 1) { 
    for(int i = 0; i < 16; i++){
    servo.writeDegree(i, pos);              
    delay(1);                      
    }
  }  
  
  /* detach all the servos */
  for(int i = 0; i < 16; i++){
    servo.dettach(i);
  }
  delay(5000);
}
