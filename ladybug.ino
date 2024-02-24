#include "PAMI_interface.h"
#include "pinout.h"

bool inYellowTeam = true;
int pamiId = 1;

long MATicks = 0;
long MBTicks = 0;

PAMI_Interface monPAMI;


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

  monPAMI.raiseArm();

  for (int i = 0; i < pamiId; i++)
  {
    monPAMI.setLedState(true);
    delay(200);
    monPAMI.setLedState(false);
    delay(200);  
  }

  monPAMI.stopMotors();
  // timeout.start();

  if (pamiId == 1) {
    monPAMI.driveStraight(425, true, false);
    monPAMI.drivePivot(90, inYellowTeam); 
    monPAMI.driveStraight(1150, true, false);
  }else if (pamiId == 2) {
    monPAMI.driveStraight(250, true, false);
    monPAMI.drivePivot(90, inYellowTeam); 
    monPAMI.driveStraight(500, true, false);
    monPAMI.drivePivot(90, inYellowTeam); 
    monPAMI.driveStraight(250, true, false);
  }else if (pamiId == 3) {
    monPAMI.driveStraight(1350, true, false);
    monPAMI.drivePivot(90, !inYellowTeam); 
    monPAMI.driveStraight(1450, true, false);
  }
  // monPAMI.drivePivot(90, true);
}

void loop() {
  // timeout.loop();
  // monPAMI.drivePivot(90, false);
  // delay(1000);
}