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

void moveMotors(bool MAState = true, bool MBState = true, int speedA = 127.5, int speedB = 127.5, bool stop = false) {
  if(!stop){
    analogWrite(pwmA, speedA);
    digitalWrite(dirA, MAState);
    digitalWrite(frA, LOW);

    analogWrite(pwmB, speedB);
    digitalWrite(dirB, MBState);
    digitalWrite(frB, LOW);
  }else{
    digitalWrite(frA, HIGH);
    digitalWrite(frB, HIGH);
  }
}