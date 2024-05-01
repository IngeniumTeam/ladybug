#include "PAMI_interface.h"
#include "pinout.h"
// #include "Timeout.h"

bool inYellowTeam = true;
int pamiId = 1;

long MATicks = 0;
long MBTicks = 0;

long timeOutBeforeStart = 90000;
int timeOutAfterStart = 10000;

PAMI_Interface monPAMI;
Timeout timeout(&totalStop, timeOutAfterStart, false);

void setup() {
  Serial.begin(9600);
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

  // monPAMI.drivePivot(90, 0);

  if (pamiId == 1) {
    monPAMI.correctCW = 1.06;
    monPAMI.correctCCW = 1.06;

    monPAMI.driveStraight(400, true, false);
    monPAMI.drivePivot(100, !inYellowTeam); 
    monPAMI.driveStraight(80, true, false);

  }else if (pamiId == 2) {
    monPAMI.correctCW = 1.06;
    monPAMI.correctCCW = 1.00;

    monPAMI.driveStraight(430, true, false);
    monPAMI.drivePivot(78, !inYellowTeam); 
    monPAMI.driveStraight(1250, true, false);

  }else if (pamiId == 3) {
    monPAMI.correctCW = 1.10;
    monPAMI.correctCCW = 0.70;

    monPAMI.driveStraight(1250, true, false);
    monPAMI.drivePivot(90, inYellowTeam); 
    monPAMI.driveStraight(1550, true, false);
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