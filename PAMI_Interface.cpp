#include "PAMI_Interface.h"

void PAMIInterface::setup() {
  setupMotors();
}

void PAMIInterface::controlMotors(motorsDirections direction, motorsSpeeds speed = motorsSpeeds::Three) {
  if(direction == motorsDirections::Forwards){
    moveMotors(motorStates::Forward, motorStates::Forward, speed, speed);
  }else if(direction == motorsDirections::Backwards){
    moveMotors(motorStates::Backward, motorStates::Backward, speed, speed);
  }else   if(direction == motorsDirections::Lefts){
    moveMotors(motorStates::Forward, motorStates::Backward, speed, speed);
  }else   if(direction == motorsDirections::Rights){
    moveMotors(motorStates::Backward, motorStates::Forward, speed, speed);
  }else   if(direction == motorsDirections::Stops){
    moveMotors(motorStates::Stop, motorStates::Stop, speed, speed);
  }
}