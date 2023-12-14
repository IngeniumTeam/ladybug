#include "motors_controller.h"

void setupMotors() {
  // Initialisation des Pins
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(frA, OUTPUT);
  pinMode(frB, OUTPUT);
}

void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int speedA = 127.5, int speedB = 127.5) {
  if(MAState == motorStates::Forward){
    analogWrite(pwmA, speedA);
    digitalWrite(dirA, LOW);
    digitalWrite(frA, LOW);
    
  }else if(MAState == motorStates::Backward) {
    analogWrite(pwmA, speedA);
    digitalWrite(dirA, HIGH);
    digitalWrite(frA, LOW);

  }else if(MAState == motorStates::Stop) {
    digitalWrite(frA, HIGH);
  }

  if(MBState == motorStates::Forward){
    analogWrite(pwmB, speedA);
    digitalWrite(dirB, HIGH);
    digitalWrite(frB, LOW);
    
  }else if(MBState == motorStates::Backward) {
    analogWrite(pwmB, speedA);
    digitalWrite(dirB, LOW);
    digitalWrite(frB, LOW);

  }else if(MBState == motorStates::Stop) {
    digitalWrite(frB, HIGH);
  }
}