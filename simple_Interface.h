#ifndef SIMPLE_INTERFACE_H
#define SIMLE_INTERFACE_H

#include "Arduino.h" 
#include "motors_controller.h"

class SimpleInterface{
public:
  static void setup();
  static void controlMotors();

private:
  SimpleInterface();
}

#endif