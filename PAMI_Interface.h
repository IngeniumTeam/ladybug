#ifndef PAMI_INTERFACE_H
#define PAMI_INTERFACE_H

#include <Arduino.h>
#include <Servo.h>
#include <Timeout.h>
#include "pinout.h"

extern Timeout timeout;

class PAMI_Interface{
public:

  PAMI_Interface();

  int mot1PWM;
  int mot2PWM;
  int straightPWM = 150;
  int pivotPWM = 100;

  int ticksDiff = 0;
  float coeff = 1.5;
  int ticksPerTurn = 353;
  int wheelDiameter = 65; // millimetres
  int halfVehicleTrack = 57; // millimetres : c'est la demi-voie du robot
  int motorATurns;
  int motorBTurns;

  String logMessage;

  void PAMIsetup();
 
  //////////////////////////////
  // Fonctions de mouvement
  //////////////////////////////
  void drivePivot(int angle, bool clockwise);
  void driveStraight(int distance, bool forward, bool interruptable);
  void equalTicksRegulator(int maxTicks, int movement, bool interruptable);

  //////////////////////////////
  // Servomoteur
  //////////////////////////////
  void raiseArm();
  void lowerArm();
  
  //////////////////////////////
  // Capteurs / Sélecteurs
  //////////////////////////////
  bool getLimitSwitchState();
  bool getSwitchState(int id);

  //////////////////////////////
  // LED 
  //////////////////////////////
  void setLedState(bool ledState);

  //////////////////////////////
  // Moteurs de traction
  //////////////////////////////
  void stopMotors();
  void moveMotors(int power_motor1, int power_motor2);

  //////////////////////////////
  // Encodeurs
  void resetCounterA();
  void resetCounterB();
  void showTicks();


private:

};

#endif