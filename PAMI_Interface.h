#ifndef PAMI_INTERFACE_H
#define PAMI_INTERFACE_H

#include "Arduino.h" 
#include "motors_controller.h"
#include "motors_encoder.h"
#include <Servo.h>

#define servoArmPin 9
#define limitSwitchPin 13
#define switch1Pin 2
#define switch2Pin 3
#define switch3Pin 4
#define switch4Pin 5

class PAMIInterface{
public:
  // static int* MATurns = &motorATurns;
  // static int* MBTurns = &motorBTurns;

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

  static void setup();
  static void controlMotors(PAMIInterface::motorsDirections direction, PAMIInterface::motorsSpeeds speed = PAMIInterface::motorsSpeeds::Three);
  static void raiseArm();
  static void lowerArm();
  static bool getLimitSwitchState();
  bool PAMIInterface::getSwitchState(int id);

private:
  PAMIInterface();
};

#endif