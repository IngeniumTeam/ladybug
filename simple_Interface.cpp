#include "simpleInterface.h"

void setup() {
  setupMotors();
  moveMotors(true, true);
}

enum motorsDirections{
  Forward,
  Backward,
  Left,
  Right,
  Stop,
};

void controlMotors(motorsDirections direction) {
  if(direction == motorsDirections.Forward){
    analogWrite(pwmA, 255); // Vitesse max
    digitalWrite(dirA, HIGH); // Sens normal
    digitalWrite(frA, LOW);
  }
}