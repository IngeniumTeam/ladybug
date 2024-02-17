#include "PAMI_interface.h"
#include "pinout.h"

bool inBlueTeam = true;
int pamiId = 1;

long MATicks = 0;
long MBTicks = 0;

PAMI_Interface monPAMI;


void setup() {
  Serial.begin(9600);

  initialize_encoders();
  
  monPAMI.PAMIsetup();

  inBlueTeam = monPAMI.getSwitchState(4);

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
    monPAMI.driveStraight(550, true, false);
    monPAMI.drivePivot(100, inBlueTeam); 
  }else if (pamiId == 2) {
    monPAMI.driveStraight(250, true, false);
    monPAMI.drivePivot(95, inBlueTeam); 
    monPAMI.driveStraight(500, true, false);
    monPAMI.drivePivot(110, inBlueTeam); 
  }else if (pamiId == 3) {
    monPAMI.driveStraight(1350, true, false);
    monPAMI.drivePivot(105, !inBlueTeam); 
  }

  monPAMI.driveStraight(100000, true, true);
  monPAMI.lowerArm();
}

void loop() {
  timeout.loop();
  // monPAMI.drivePivot(90, false);
  // delay(1000);
}