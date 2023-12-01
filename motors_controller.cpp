#include "motors_controller.h"
int MATicksForATurn = 0;
int MBTicksForATurn = 0;

void setupMotors(int MATicksTurns, int MBTicksTurns) {
  MATicksForATurn = MATicksTurns;
  MBTicksForATurn = MBTicksTurns;

  // Initialisation des Pins
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(frA, OUTPUT);
  pinMode(frB, OUTPUT);

  pinMode(encoder1A, INPUT_PULLUP);
  pinMode(encoder2A, INPUT_PULLUP);
  attachInterrupt(0,MACounter, CHANGE);
  attachInterrupt(1,MBCsounter, CHANGE);
}

void moveMotors(motorStates MAState = motorStates::Forward, motorStates MBState = motorStates::Forward, int speedA = 127.5, int speedB = 127.5) {
  if(MAState == motorStates::Forward){
    analogWrite(pwmA, speedA);
    digitalWrite(dirA, LOW);
    digitalWrite(frA, LOW);
    
  }else if(MAState == motorStates::Backward) {
    analogWrite(pwmA, speedA);
    digitalWrite(dirA, HIGH);
    digitalWrite(frA, LOW);

  }else if(MAState == motorStates::Stop) {
    digitalWrite(frA, HIGH);
  }

  if(MBState == motorStates::Forward){
    analogWrite(pwmB, speedA);
    digitalWrite(dirB, HIGH);
    digitalWrite(frB, LOW);
    
  }else if(MBState == motorStates::Backward) {
    analogWrite(pwmB, speedA);
    digitalWrite(dirB, LOW);
    digitalWrite(frB, LOW);

  }else if(MBState == motorStates::Stop) {
    digitalWrite(frB, HIGH);
  }
}

void MACounter()
{
  byte state=PIND;
  
  state|=B11101011;  // mask pour ne regarder que les changements sur 2 et 4 
  // Modifier le MASK  B01111011 par BXXXXXXXX mettre des 0 là où sont les pins utilisés par l'encodeur
  if( state!=MALaststate)
  {
    (((state&(1<<encoder1A))>>encoder1A)^((state&(1<<encoder1A))>>encoder1A))?MACount--:MACount++;

    if(MBCount >= MATicksForATurn) {
      motorATurns++;
    }

    MALaststate=state;
  }
}

void MBCounter()
{
  byte state=PIND;
  
  state|=B11101011;  // mask pour ne regarder que les changements sur 2 et 4 
  // Modifier le MASK  B01111011 par BXXXXXXXX mettre des 0 là où sont les pins utilisés par l'encodeur
  if( state!=MBLaststate)
  {
    (((state&(1<<encoder1B))>>encoder1B)^((state&(1<<encoder1B))>>encoder1B))?MBCount--:MBCount++;

    if(MBCount >= MBTicksForATurn) {
      motorBTurns++;
    }

    MBLaststate=state;
  }
}