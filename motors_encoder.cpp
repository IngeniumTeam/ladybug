#include "HardwareSerial.h"
#include "Arduino.h"
#include "motors_encoder.h"

int motorATurns = 0;
int motorBTurns = 0;

int MATicksForATurn = 0;
int MBTicksForATurn = 0;

volatile int MACount = 0;
volatile int MBCount = 0;

void setupEncoder(int MATicksTurns, int MBTicksTurns) {
  MATicksForATurn = MATicksTurns;
  MBTicksForATurn = MBTicksTurns;

  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderABreak, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  pinMode(encoderBBreak, INPUT_PULLUP);

  attachInterrupt(1, MACounter, RISING);
  attachInterrupt(0,MBCounter, RISING);
}

void MACounter()
{
  int encoderARead = analogRead(encoderA);

  if (encoderARead > 512) MACount--;
  if (encoderARead < 512) MACount++;

  // Serial.println(MACount);

  if(MACount >= MATicksForATurn) {
    motorATurns++;
  }

  if(MACount <= -MATicksForATurn) {
    motorATurns--;
  }
}

void MBCounter()
{
  int encoderBRead = analogRead(encoderB);

  if (encoderBRead > 512) MBCount--;
  if (encoderBRead < 512) MBCount++;

  if(MBCount >= MBTicksForATurn) {
    motorBTurns++;
  }
}


void resetCounterA() {
  motorATurns = 0;
  MACount = 0;
}

void resetCounterB() {
  motorBTurns = 0;
  MBCount = 0;
}