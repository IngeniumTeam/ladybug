#ifndef MOTORS_ENCODER_H
#define MOTORS_ENCODER_H

#include "Arduino.h"

#define encoderA A1
#define encoderABreak 3
#define encoderB A0
#define encoderBBreak 2

extern int motorATurns;
extern int motorBTurns;
extern volatile int MATicks;
extern volatile int MBTicks;

void setupEncoder(int MATicksTurns, int MBTicksTurns);
void MACounter();
void MBCounter();
void resetCounterA();
void resetCounterB();

#endif
