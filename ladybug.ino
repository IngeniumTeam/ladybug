#include "PAMI_interface.h"

bool inYellowTeam = true;
int pamiId = 1;
int state = 1;

void setup() {
  PAMIInterface::setup();

  inYellowTeam = PAMIInterface::getSwitchState(4);

  if(PAMIInterface::getSwitchState(1)) {
    pamiId = 1;
  }else if(PAMIInterface::getSwitchState(2)) {
    pamiId = 2;
  }else if(PAMIInterface::getSwitchState(3)) {
    pamiId = 3;
  }

  Serial.begin(9600);
  PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Two);
}

void loop() {
  PAMIInterface::fixMotors(0.8);
  // Serial.println("A : " + String(MATicks) + " B : " + String(MBTicks));

  // if(motorATurns <= -1) {
  //   PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Stops);
  //   resetCounterA();
  //   delay(1000);
  //   PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Two);
  // }

  // switch (pamiId) 
  // {
  //   case 1:
  //     switch (state)
  //     {
  //       case 1:
  //         PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Forwards, PAMIInterface::motorsSpeeds::Two);
  //         if(motorATurns == -3) {
  //           resetCounterA();
  //           state++;
  //         }
  //         break;
  //       case 2:
  //         PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Lefts, PAMIInterface::motorsSpeeds::Two);
  //         if(motorATurns == -2) {
  //           resetCounterA();
  //           state++;
  //         }
  //       case 2:
  //         PAMIInterface::controlMotors(PAMIInterface::motorsDirections::Lefts, PAMIInterface::motorsSpeeds::Two);
  //         if(motorATurns == -2) {
  //           resetCounterA();
  //           state++;
  //         }
  //         break;
  //     }
  //     break;

  //   case 2:

  //     break;

  //   case 3:

  //     break;
  // }
}
