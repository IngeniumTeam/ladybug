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

void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int speedA = 127.5, int speedB = 127.5) {
  if(MAState == motorStates::Forward){
    analogWrite(pwmA, speedA);
    digitalWrite(aIn1, LOW);
    digitalWrite(aIn2, HIGH);
    
  }else if(MAState == motorStates::Backward) {
    analogWrite(pwmA, speedA);
    digitalWrite(aIn1, HIGH);
    digitalWrite(aIn2, LOW);

  }else if(MAState == motorStates::Stop) {
    digitalWrite(aIn1, LOW);
    digitalWrite(aIn2, LOW);
  }

  if(MBState == motorStates::Forward){
    analogWrite(pwmB, speedB);
    digitalWrite(bIn1, HIGH);
    digitalWrite(bIn2, LOW);
    
  }else if(MBState == motorStates::Backward) {
    analogWrite(pwmB, speedB);
    digitalWrite(bIn1, LOW);
    digitalWrite(bIn2, HIGH);

  }else if(MBState == motorStates::Stop) {
    digitalWrite(bIn1, LOW);
    digitalWrite(bIn2, LOW);
  }
}