#include "Arduino.h"
#include "motors_encoder.h"

int MATicks = 0;
int MBTicks = 0;

void setupEncoder(int MATicksTurns, int MBTicksTurns) {
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