#include "HardwareSerial.h"
#include "Arduino.h"
#include "motors_encoder.h"

int motorATurns = 0;
int motorBTurns = 0;

int MATicksForATurn = 0;
int MBTicksForATurn = 0;

volatile int MATicks = 0;
volatile int MBTicks = 0;

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

  if (encoderARead > 512) MATicks++;
  if (encoderARead < 512) MATicks--;

  if(MATicks >= MATicksForATurn) {
    motorATurns++;
    MATicks = MATicks - MATicksForATurn;
  }

  if(MATicks <= -MATicksForATurn) {
    motorATurns--;
    MATicks = MATicks + MATicksForATurn;
  }
}

void MBCounter()
{
  // Serial.println("MB Count !!");
  int encoderBRead = analogRead(encoderB);

  if (encoderBRead > 512) MBTicks--;
  if (encoderBRead < 512) MBTicks++;
  
  if(MBTicks >= MBTicksForATurn) {
    motorBTurns++;
    MBTicks = MBTicks - MBTicksForATurn;
  }

  if(MBTicks <= -MBTicksForATurn) {
    motorBTurns--;
    MBTicks = MBTicks + MBTicksForATurn;
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