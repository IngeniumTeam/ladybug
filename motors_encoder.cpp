#include "motors_encoder.h"

int MATicksForATurn = 0;
int MBTicksForATurn = 0;

volatile int MACount = 0;
volatile byte MALaststate = 0;
volatile int MBCount = 0;
volatile byte MBLaststate = 0;

void setupEncoder(int MATicksTurns, int MBTicksTurns) {
  MATicksForATurn = MATicksTurns;
  MBTicksForATurn = MBTicksTurns;

  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderABreak, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  pinMode(encoderBBreak, INPUT_PULLUP);

  attachInterrupt(0,MACounter, CHANGE);
  attachInterrupt(1,MBCounter, CHANGE);
}

void MACounter()
{
  byte state=PIND;
  
  state|=B11101011;  // mask pour ne regarder que les changements sur 2 et 4 
  // Modifier le MASK  B01111011 par BXXXXXXXX mettre des 0 là où sont les pins utilisés par l'encodeur
  if( state!=MALaststate)
  {
    (((state&(1<<encoderA))>>encoderA)^((state&(1<<encoderA))>>encoderA))?MACount--:MACount++;

    if(MACount >= MATicksForATurn) {
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
    (((state&(1<<encoderB))>>encoderB)^((state&(1<<encoderB))>>encoderB))?MBCount--:MBCount++;

    if(MBCount >= MBTicksForATurn) {
      motorBTurns++;
    }

    MBLaststate=state;
  }
}