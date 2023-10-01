#ifndef MOTORS_CONTROLLER_H
#define MOTORS_CONTROLLER_H

#include "Arduino.h"

#define dirA 12
#define dirB 13
#define pwmA 3
#define pwmB 11
#define frA 9
#define frB 8 

void setupMotors();
void moveMotors();

#endif
