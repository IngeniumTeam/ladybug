#include "Arduino.h"
#include "PAMI_Interface.h"

Servo armMotor;

motorStates MALastState = motorStates::Stop;
motorStates MBLastState = motorStates::Stop;
int currentSpeed = 0;

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
  bool correctDirection = false;

  if(direction == PAMIInterface::motorsDirections::Forwards){
    MALastState = motorStates::Forward;
    MBLastState = motorStates::Forward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Backwards){
    MALastState = motorStates::Backward;
    MBLastState = motorStates::Backward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Lefts){
    MALastState = motorStates::Forward;
    MBLastState = motorStates::Backward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Rights){
    MALastState = motorStates::Backward;
    MBLastState = motorStates::Forward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Stops){
    MALastState = motorStates::Stop;
    MBLastState = motorStates::Stop;
    correctDirection = true;
  }

  if(correctDirection) {
    moveMotors(MALastState, MBLastState, speed, speed);
    currentSpeed = speed;
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

static void PAMIInterface::fixMotors(int coef) {
  int diff = MATicks - MBTicks;
  int MASpeed = max(0, min(255, currentSpeed - coef * diff));
  int MBSpeed = max(0, min(255, currentSpeed + coef * diff));

  Serial.println("A : " + String(MASpeed) + " B : " + String(MBSpeed) + " Diff : " + diff);
  moveMotors(MALastState, MBLastState, MASpeed, MBSpeed);
}
