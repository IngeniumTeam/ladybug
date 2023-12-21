#include "PAMI_interface.h"

void setup() {
  PAMIInterface::setup();
  Serial.begin(9600);
  PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Three);
}

void loop() {
<<<<<<< HEAD
  if(motorATurns >= 1) {
    PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Stops);
    resetCounterA();
    delay(1000);
    PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Three);
  }
=======
>>>>>>> 58d7c56be47c77c8bafa29c65d19540dfb2ea7db

}