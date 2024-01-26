#ifndef MOTORS_CONTROLLER_H
#define MOTORS_CONTROLLER_H

#include "Arduino.h"
#include "motors_encoder.h"

#define aIn1 7
#define aIn2 8
#define bIn1 11
#define bIn2 12
#define pwmA 5
#define pwmB 6
#define STBY 10

volatile long ticksA;
volatile long ticksB;

enum motorStates{
  Forward,
  Backward,
  Stop,
};

void setupMotors();
void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int maxTicks, int speed = 127.55);

#endif
