#ifndef MOTORS_CONTROLLER_H
#define MOTORS_CONTROLLER_H

#include "Arduino.h"

#define aIn1 7
#define aIn2 8
#define bIn1 11
#define bIn2 12
#define pwmA 5
#define pwmB 6
#define STBY 10

enum motorStates{
  Forward,
  Backward,
  Stop,
};

void setupMotors();
void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int speedA = 127.5, int speedB = 127.5);

#endif
