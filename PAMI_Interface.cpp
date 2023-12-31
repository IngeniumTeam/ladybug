#include "Arduino.h"
#include "PAMI_Interface.h"

Servo armMotor;

void PAMIInterface::setup() {
  setupMotors();
  setupEncoder(355, 385);
  armMotor.attach(servoArmPin);
  pinMode(limitSwitchPin, INPUT);
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);
  
  pinMode(ledPin, OUTPUT);

  // armMotor.write(180);
}

void PAMIInterface::controlMotors(PAMIInterface::motorsDirections direction, PAMIInterface::motorsSpeeds speed = PAMIInterface::motorsSpeeds::Three) {
  if(direction == PAMIInterface::motorsDirections::Forwards){
    moveMotors(motorStates::Forward, motorStates::Forward, speed, speed);
  }else if(direction == PAMIInterface::motorsDirections::Backwards){
    moveMotors(motorStates::Backward, motorStates::Backward, speed, speed);
  }else   if(direction == PAMIInterface::motorsDirections::Lefts){
    moveMotors(motorStates::Forward, motorStates::Backward, speed, speed);
  }else   if(direction == PAMIInterface::motorsDirections::Rights){
    moveMotors(motorStates::Backward, motorStates::Forward, speed, speed);
  }else   if(direction == PAMIInterface::motorsDirections::Stops){
    moveMotors(motorStates::Stop, motorStates::Stop, speed, speed);
  }
}

void PAMIInterface::raiseArm() {
  armMotor.write(70);
}

void PAMIInterface::lowerArm() {
  armMotor.write(30);
}

bool PAMIInterface::getLimitSwitchState() {
  return digitalRead(limitSwitchPin);
}

bool PAMIInterface::getSwitchState(int id) {
  int switchPin;

  if (id == 1) {
    switchPin = switch1Pin;
  }else if (id == 2) {
    switchPin = switch2Pin;
  }else if (id == 3) {
    switchPin = switch3Pin;
  }else if (id == 4) {
    switchPin = switch4Pin;
  }

  return analogRead(switchPin);
}

void PAMIInterface::setLedState(bool ledState) {
  digitalWrite(ledPin, ledState);
}
