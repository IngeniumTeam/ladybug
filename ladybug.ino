#include "PAMI_interface.h"
#include <Servo.h>

Servo clawMotor;
int motorPin = 5;

void setup() {
  // PAMIInterface::setup();
  // PAMIInterface::controlMotors(motorsDirections::Stops, motorsSpeeds::Three);

  clawMotor.attach(motorPin);
}

void loop() {
  clawMotor.write(0);        //Mettre le servo à 0º
  delay(4000);
  clawMotor.write(90);       //Mettre le servo à 90º
  delay (4000);
  clawMotor.write(180);      //Mettre le servo à 180º
  delay (4000); 
}