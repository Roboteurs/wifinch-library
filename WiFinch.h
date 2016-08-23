#ifndef _WIFINCH_H
#define _WIFINCH_H

#include "Arduino.h"

/*
 * @Breif WiFinch class for driving PWM servo hardware
 * 
 */
class WiFinch {
  
 public:
  WiFinch( );
  void begin(void);
  void init(void);
  void attach(char servonum);
  void writeDegree(char servonum, int angle);
  void writeHalfDegree(char servonum, int angle);
  void dettach(char servonum);

 private:
  void writeBus(char address, char reg, char data);
};

#endif
