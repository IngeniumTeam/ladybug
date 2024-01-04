#include "PAMI_interface.h"

bool inYellowTeam = true;
int pamiId = 1;

void setup() {
  PAMIInterface::setup();

  inYellowTeam = PAMIInterface::getSwitchState(4);

  if(PAMIInterface::getSwitchState(1)) {
    pamiId = 1;
  }else if(PAMIInterface::getSwitchState(2)) {
    pamiId = 2;
  }else if(PAMIInterface::getSwitchState(3)) {
    pamiId = 3;
  }

  Serial.begin(9600);
  // PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::One);
}

void loop() {
  // if(motorATurns <= -1) {
  //   PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Stops);
  //   resetCounterA();
  //   delay(1000);
  //   PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Three);
  // }
}