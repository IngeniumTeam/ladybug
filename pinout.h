#ifndef pinout_h
#define pinout_h

#include "Arduino.h" 

extern long MATicks;
extern long MBTicks;

#define aIn1 8
#define aIn2 7
#define bIn1 12
#define bIn2 11
#define pwmA 5
#define pwmB 6  
#define STBY 10

#define servoArmPin 9
#define limitSwitchPin 13
#define switch1Pin A2
#define switch2Pin A3
#define switch3Pin A4
#define switch4Pin A5
#define ledPin 4

#define encoderA A1
#define encoderABreak 3
#define encoderB A0
#define encoderBBreak 2

#endif