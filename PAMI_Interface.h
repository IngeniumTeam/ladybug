#ifndef PAMI_INTERFACE_H
#define PAMI_INTERFACE_H

#include "Arduino.h" 
#include "motors_controller.h"
#include <Servo.h>

#define servoArmPin 10
#define limitSwitchPin 4

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
  static void raiseArm();
  static void lowerArm();
  static bool getLimitSwitchState();
  static int motorTurns = 0;

private:
  PAMIInterface();
};

#endif