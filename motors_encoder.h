#ifndef MOTORS_ENCODER_H
#define MOTORS_ENCODER_H

#include "Arduino.h"

#define encoderA A1
#define encoderABreak 3
#define encoderB A0
#define encoderBBreak 2

<<<<<<< HEAD
extern int motorATurns;
extern int motorBTurns;
=======
int motorATurns = 0;
int motorBTurns = 0;
>>>>>>> 58d7c56be47c77c8bafa29c65d19540dfb2ea7db

void setupEncoder(int MATicksTurns, int MBTicksTurns);
void MACounter();
void MBCounter();
<<<<<<< HEAD
void resetCounterA();
void resetCounterB();
=======
>>>>>>> 58d7c56be47c77c8bafa29c65d19540dfb2ea7db

#endif
