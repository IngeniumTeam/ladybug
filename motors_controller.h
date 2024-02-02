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

int mot1PWM;
int mot2PWM;

int ticksDiff = 0;
float coeff = 1.5;
int ticksPerTurn = 353;
int wheelDiameter = 65; // millimetres
int halfVehicleTrack = 57; // millimetres : c'est la demi-voie du robot
 
enum motorStates{
  Forward = 1,
  Backward = -1,
  Stop = 0,
};

void setupMotors();
void moveMotor(int motorNumber, int power);
void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int maxTicks = 0, int speed = 127.55);

#endif
