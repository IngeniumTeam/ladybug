#include "pinout.h"

void initialize_encoders()
{
  
  pinMode(encoderA, INPUT);
  pinMode(encoderABreak, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderABreak), MACounter, RISING);

  pinMode(encoderB, INPUT);
  pinMode(encoderBBreak, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderBBreak), MBCounter, RISING);

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
  if (digitalRead(encoderB))
  {
    MBTicks++;
  }
  else
  {
    MBTicks--;
  }
}