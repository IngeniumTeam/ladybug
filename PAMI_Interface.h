#ifndef PAMI_INTERFACE_H
#define PAMI_INTERFACE_H

#include "Arduino.h" 
#include "motors_controller.h"

enum motorsDirections{
  Forwards,
  Backwards,
  Lefts,
  Rights,
  Stops,
};

enum motorsSpeeds{
  One = 64,
  Two = 127,
  Three = 191,
  For = 255,
};

class PAMIInterface{
public:
  static void setup();
  static void controlMotors(motorsDirections direction, motorsSpeeds speed = motorsSpeeds::Three);

private:
  PAMIInterface();
};

#endif