#ifndef MOTORS_ENCODER_H
#define MOTORS_ENCODER_H

#include "Arduino.h"

#define encoderA 1
#define encoderABreak 3
#define encoderB 0
#define encoderBBreak 2

int motorATurns = 0;
int motorBTurns = 0;

void setupEncoder(int MATicksTurns, int MBTicksTurns);
void MACounter();
void MBCounter();

#endif
