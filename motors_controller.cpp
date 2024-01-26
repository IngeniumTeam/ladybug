#include "motors_controller.h"

void setupMotors() {
  // Initialisation des Pins
  pinMode(aIn1, OUTPUT);
  pinMode(aIn2, OUTPUT);
  pinMode(bIn1, OUTPUT);
  pinMode(bIn2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);

  pinMode(STBY,OUTPUT);
  digitalWrite(STBY, HIGH);
}

void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int maxTicks, int speed = 127.55) {
  if(MAState == motorStates::Stop) {
    digitalWrite(aIn1, HIGH);
    digitalWrite(aIn2, HIGH);
  }else if(MBState == motorStates::Stop) {
    digitalWrite(bIn1, HIGH);
    digitalWrite(bIn2, HIGH);
  }else {
    int signMot1 = 0
    int signMot2 = 0

    if(MAState == motorStates::Forward) 
      signMot1 = 1
    else if(MAState == motorStates::Backward) 
      signMot1 = -1

    if(MBState == motorStates::Forward) 
      signMot2 = 1
    else if(MBState == motorStates::Backward) 
      signMot2 = -1

    while (max(abs(MATicks), abs(MBTicks)) < maxTicks)
    {
      if (abs(MATicks) < maxTicks)
      {
        mot1PWM = min(255, speed - ticksDiff*coeff);
        moveMotor(1, signMot1 * mot1PWM);
      }    
      if (abs(MBTicks) < maxTicks)
      {
        mot2PWM = min(255, speed + ticksDiff*coeff);
        moveMotor(2, signMot2 * mot2PWM);
      }
      
      ticksDiff = abs(MATicks) - abs(MBTicks);
    }
  }
}

private void moveMotor(int motorNumber, int power)
{
  digitalWrite(STBY_PIN, HIGH);
  if(motorNumber == 1)
  {
    if (power > 0)
    {
      digitalWrite(aIn1, HIGH);
      digitalWrite(aIn2, LOW);
      analogWrite(pwmA, power);
    }
    else
    {
      digitalWrite(aIn1, LOW);
      digitalWrite(aIn2, HIGH);
      analogWrite(pwmA, -power);      
    }
  }
  else if (motorNumber == 2)
  {
    if (power > 0)
    {
      digitalWrite(bIn1, HIGH);
      digitalWrite(bIn2, LOW);
      analogWrite(pwmB, power);
    }
    else
    {
      digitalWrite(bIn1, LOW);
      digitalWrite(bIn2, HIGH);
      analogWrite(pwmB, -power);      
    }
  }
}