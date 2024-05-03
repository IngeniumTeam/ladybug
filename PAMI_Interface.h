#ifndef PAMI_INTERFACE_H
#define PAMI_INTERFACE_H

#include <Arduino.h>
#include <Servo.h>
#include "Timeout.h"
#include "pinout.h"

extern Timeout timeout;

class PAMI_Interface{
public:

  PAMI_Interface();

  int mot1PWM;
  int mot2PWM;
  int minPWM = 95;
  int straightPWM = 120;
  int pivotPWM = 120;
  int maxMotorDrive = 255;
  int minMotorDrive = 60;

  int ticksDiff = 0;
  float distanceDiff = 0.0;
  float coeff = 1.5;
  int ticksPerTurn = 1092;
  int ticksPerTurn_motA = 1092;
  int ticksPerTurn_motB = 1092;
  int wheelDiameter = 65; // millimetres
  float wheelDiameter_motA = 65.0;
  float wheelDiameter_motB = 65.0;
  int extraDist = 0; // millimetres
  float halfVehicleTrack = 60.0; // millimetres : c'est la demi-voie du robot
  
  int motorATurns;
  int motorBTurns;

  float correctCW = 1.0;
  float correctCCW = 1.0;

  int ticksForAccel = 1000;
  int distanceAccel = 80;

  String logMessage;

  void PAMIsetup();
 
  //////////////////////////////
  // Fonctions de mouvement
  //////////////////////////////
  void drivePivot(int angle, bool clockwise);
  void driveStraight(int distance, bool forward, bool interruptable);
  void equalTicksRegulator(int maxTicks, int movement, bool interruptable);
  void equalDistRegulator(int distance, int movement, bool interruptable);

  //////////////////////////////
  // Servomote  ur
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