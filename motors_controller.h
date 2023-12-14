#ifndef MOTORS_CONTROLLER_H
#define MOTORS_CONTROLLER_H

#include "Arduino.h"

#define dirA 12
#define dirB 13
#define pwmA 3
#define pwmB 11
#define frA 9
#define frB 8 

enum motorStates{
  Forward,
  Backward,
  Stop,
};

void setupMotors();
void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int speedA = 127.5, int speedB = 127.5);

#endif
