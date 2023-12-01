#ifndef MOTORS_CONTROLLER_H
#define MOTORS_CONTROLLER_H

#include "Arduino.h"

#define dirA 12
#define dirB 13
#define pwmA 3
#define pwmB 11
#define frA 9
#define frB 8 

#define encoder1A 2
#define encoder2A 4

int motorATurns = 0;
int motorBTurns = 0;

volatile int MACounts = 0; // comptage de tick d'encoder  qui sera incrémenté sur interruption " On change " sur l'interruption matériel 0 qui se fait sur le pin 2
volatile byte MALaststate = 0;  // etat précédent de l'encodeur 

enum motorStates{
  Forward,
  Backward,
  Stop,
};

void setupMotors(int MATicksTurns, int MBTicksTurns);
void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int speedA = 127.5, int speedB = 127.5);

#endif
