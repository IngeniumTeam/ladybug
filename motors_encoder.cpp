#include "Arduino.h"
#include "motors_encoder.h"

int ticksPerTurn = 353;
int wheelDiameter = 65; // millimetres
int halfVehicleTrack = 57; // millimetres : c'est la demi-voie du robot

int MATicks = 0;
int MBTicks = 0;

void setupEncoder(int MATicksTurns, int MBTicksTurns) {
  MATicksForATurn = MATicksTurns;
  MBTicksForATurn = MBTicksTurns;

  pinMode(encoderA, INPUT);
  pinMode(encoderABreak, INPUT);
  pinMode(encoderB, INPUT);
  pinMode(encoderBBreak, INPUT);

  attachInterrupt(1, MACounter, RISING);
  attachInterrupt(0, MBCounter, RISING);
}

void MACounter()
{
  if (!digitalRead(encoderA))
  {
    MATicks++;
  }
  else
  {
    MATicks--;
  }
}

void MBCounter()
{
  if (!digitalRead(encoderB))
  {
    MBTicks++;
  }
  else
  {
    MBTicks--;
  }
}


void resetCounterA() {
  motorATurns = 0;
  MATicks = 0;
}

void resetCounterB() {
  motorBTurns = 0;
  MBTicks = 0;
}