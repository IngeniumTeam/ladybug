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

void moveMotor(int motorNumber, int power)
{
  digitalWrite(STBY, HIGH);
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

void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int maxTicks, int speed = 127.55) {
  while (max(abs(MATicks), abs(MBTicks)) < maxTicks)
  {
    if (abs(MATicks) < maxTicks)
    {
      mot1PWM = min(255, speed - ticksDiff*coeff);
      moveMotor(1, MAState * mot1PWM);
    }    
    if (abs(MBTicks) < maxTicks)
    {
      mot2PWM = min(255, speed + ticksDiff*coeff);
      moveMotor(2, MBState * mot2PWM);
    }
    
    ticksDiff = abs(MATicks) - abs(MBTicks);
  }
}