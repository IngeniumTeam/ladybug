#include "PAMI_interface.h"

void setup() {
  PAMIInterface::setup();
  Serial.begin(9600);
  PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Three);
}

void loop() {
  // if(motorATurns <= -1) {
  //   PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Stops);
  //   resetCounterA();
  //   delay(1000);
  //   PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Three);
  // }
}