#ifndef PAMI_INTERFACE_H
#define PAMI_INTERFACE_H

#include "Arduino.h" 
#include "motors_controller.h"
#include "motors_encoder.h"
#include <Servo.h>
#include <PID_v1.h>

#define servoArmPin 9
#define limitSwitchPin 13
#define switch1Pin A2
#define switch2Pin A3
#define switch3Pin A4
#define switch4Pin A5
#define ledPin 4

class PAMIInterface{
public:
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
    Four = 255,
  };

  static void setup();
  static void controlMotors(PAMIInterface::motorsDirections direction, PAMIInterface::motorsSpeeds speed = PAMIInterface::motorsSpeeds::Three);
  static void raiseArm();
  static void lowerArm();
  static bool getLimitSwitchState();
  static bool getSwitchState(int id);
  static void setLedState(bool ledState);
  static void fixMotors(int coef);

private:
  PAMIInterface();
};

#endif