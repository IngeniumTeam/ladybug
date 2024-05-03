#include "PAMI_interface.h"
#include "pinout.h"

bool inYellowTeam = true;
int pamiId = 1;

long MATicks = 0;
long MBTicks = 0;

long timeOutBeforeStart = 90000;
int timeOutAfterStart = 10000;

PAMI_Interface monPAMI;
Timeout timeout(&totalStop, timeOutAfterStart, false);

void setup() {
  Serial.begin(115200);
  initialize_encoders();
  monPAMI.PAMIsetup();

  inYellowTeam = monPAMI.getSwitchState(4);

  if(monPAMI.getSwitchState(1)) {
    pamiId = 1;
  }else if(monPAMI.getSwitchState(2)) {
    pamiId = 2;
  }else if(monPAMI.getSwitchState(3)) {
    pamiId = 3;
  }

  Serial.println(pamiId);

  monPAMI.raiseArm();

  for (int i = 0; i < pamiId; i++)
  {
    monPAMI.setLedState(true);
    delay(200);
    monPAMI.setLedState(false);
    delay(200);
  }

  monPAMI.stopMotors();

  Serial.print("PAMI n°" + String(pamiId) + " in ");
  Serial.print(inYellowTeam ? "Yellow" : "Blue");
  Serial.println(" team");
  
  while(digitalRead(limitSwitchPin)) // Attente tirette
  {
    Serial.println("Waiting for start signal! Switch input = " + String(digitalRead(limitSwitchPin))); 
    delay(100);
  }
  Serial.println("Countdown started!");
  // delay(timeOutBeforeStart);  
  
  Serial.println("Launch !");
  // timeout.start();

  // monPAMI.driveStraight(800, true, false);

  if (pamiId == 1) {
    monPAMI.correctCW = 1.0;
    monPAMI.correctCCW = 0.97;

    monPAMI.ticksPerTurn_motA = 969;
    monPAMI.ticksPerTurn_motB = 983;
    monPAMI.wheelDiameter_motA = 66.2;
    monPAMI.wheelDiameter_motB = 66.0;
    monPAMI.halfVehicleTrack = 59.5;
    monPAMI.extraDist = 0; // Doit etre calibré!

    // Strategie de match
    monPAMI.driveStraight(400, true, false);
    monPAMI.drivePivot(90, !inYellowTeam); 
    monPAMI.driveStraight(80, true, false);

    // Mouvements de test
    // monPAMI.drivePivot(180, false); 
    // monPAMI.driveStraight(500, true, false);
    
  }else if (pamiId == 2) {
    monPAMI.correctCW = 1.0; // Doit etre calibré!
    monPAMI.correctCCW = 1.5; // Doit etre calibré!

    monPAMI.ticksPerTurn_motA = 959;
    monPAMI.ticksPerTurn_motB = 970;
    monPAMI.wheelDiameter_motA = 51.0;
    monPAMI.wheelDiameter_motB = 81.0;
    monPAMI.halfVehicleTrack = 59.5;
    monPAMI.extraDist = 0; // Doit etre calibré!

    // Strategie de match
    monPAMI.driveStraight(430, true, false);
    monPAMI.drivePivot(70, !inYellowTeam); 
    monPAMI.driveStraight(1260, true, false);
    
    // Mouvements de test
    // monPAMI.driveStraight(1000, true, false);
    // monPAMI.drivePivot(90, 0); 
    // monPAMI.drivePivot(90, 1); 

  }else if (pamiId == 3) {
    monPAMI.correctCW = 1.00; // Doit etre calibré!
    monPAMI.correctCCW = 1.00; // Doit etre calibré!

    monPAMI.ticksPerTurn_motA = 970;  // Doit etre calibré!
    monPAMI.ticksPerTurn_motB = 970; // Doit etre calibré!
    monPAMI.wheelDiameter_motA = 54.0;
    monPAMI.wheelDiameter_motB = 76.0;
    monPAMI.halfVehicleTrack = 60.0; // Doit etre calibré!
    monPAMI.extraDist = 0; // Doit etre calibré!

    // Strategie de match
    // monPAMI.driveStraight(1250, true, false);
    // monPAMI.drivePivot(90, inYellowTeam); 
    // monPAMI.driveStraight(1550, true, false);

    // Mouvements de test
    monPAMI.driveStraight(1000, true, false);
    // monPAMI.drivePivot(90, 0); 
    // monPAMI.drivePivot(90, 1);    
  }

  monPAMI.lowerArm();

  while (true) {
    monPAMI.setLedState(true);
    delay(200);
    monPAMI.setLedState(false);
    delay(200);  
  }
}

void loop() {
  timeout.loop();
  // monPAMI.drivePivot(90, false);
  // delay(1000);
}

void totalStop() {
  digitalWrite(STBY, LOW);
  while (true) {
    monPAMI.setLedState(true);
    delay(200);
    monPAMI.setLedState(false);
    delay(200);  
  }
}