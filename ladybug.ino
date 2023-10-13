#include "PAMI_interface.h"

void setup() {
  PAMIInterface::setup();
  Serial.begin(9600);
  // PAMIInterface::controlMotors(motorsDirections::Stops, motorsSpeeds::Three);
}

void loop() {
  bool positionBouton = PAMIInterface::getLimitSwitchState();

  if(positionBouton == HIGH) 
  // Si le bouton est appuyé, il est connecté au 5V! (HIGH)
  {
    Serial.println("Bouton appuyé");
  }
  delay(100);
}