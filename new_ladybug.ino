#include <Motor.h>

#define encoderA A1
#define encoderABreak 3
#define encoderB A0
#define encoderBBreak 2

#define switch1Pin A2
#define switch2Pin A3
#define switch3Pin A4
#define switch4Pin A5

#define limitSwitchPin 13
#define ledPin 4

Motor left(8, 7, 5, 10, 0, 255, 0, 180);
Motor right(12, 11, 6, 10, 0, 255, 0, 180);

int MATicks = 0;
int MBTicks = 0;

const float ATicksPerTurn = 960.0;
const float BTicksPerTurn = 980.0;
const int wheelPerimeter = 66 * PI;
const float halfVehicleWidth = 59.5;

int pamiId = 1;
bool inYellowTeam = false;

void setup() {
  Serial.begin(9600);
  while(digitalRead(limitSwitchPin)) {}
  delay(90000);
  pinMode(encoderA, INPUT);
  pinMode(encoderABreak, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderABreak), MACounter, RISING);

  pinMode(encoderB, INPUT);
  pinMode(encoderBBreak, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderBBreak), MBCounter, RISING);

  inYellowTeam = getSwitchState(4);

  if(getSwitchState(1)) {
    pamiId = 1;
  }else if(getSwitchState(2)) {
    pamiId = 2;
  }else if(getSwitchState(3)) {
    pamiId = 3;
  }

  Serial.println(pamiId);

  for (int i = 0; i < pamiId; i++)
  {
    digitalWrite(ledPin, true);
    delay(200);
    digitalWrite(ledPin, false);
    delay(200);
  }

  Serial.print("PAMI n°" + String(pamiId) + " in ");
  Serial.print(inYellowTeam ? "Yellow" : "Blue");
  Serial.println(" team");

  switch (pamiId) {
    case 1:
      driveStraight(300, true);
      drivePivot(90, !inYellowTeam);
      driveStraight(100, true);
      break;

    case 2:
      driveStraight(50, true);
      drivePivot(90, !inYellowTeam);
      driveStraight(1200, true);
      break;
  }
}

void loop() {

}

void driveStraight(int distance, bool forward) {
  if (forward) {
    left.backward(255);
    right.backward(255);
  }else {
    left.forward(255);
    right.forward(255);
  }
  
  MATicks = 0;
  MBTicks = 0;
  while(abs(MATicks / ATicksPerTurn) * wheelPerimeter <= distance && abs(MBTicks / BTicksPerTurn) * wheelPerimeter <= distance) {
    Serial.println(MATicks);
  }
  left.stop();
  right.stop();
}

void drivePivot(int angle, bool clockwise) {
  if (clockwise) {
    right.backward(200);
    left.forward(200);
  }else {
    right.forward(200);
    left.backward(200);
  }
  
  MATicks = 0;
  MBTicks = 0;
  while(abs(MATicks) <= ATicksPerTurn * (angle * PI / 180) * (halfVehicleWidth / wheelPerimeter) && abs(MBTicks) <= BTicksPerTurn * (angle * PI / 180) * (halfVehicleWidth / wheelPerimeter)) {
    Serial.println(MATicks);
  }
  left.stop();
  right.stop();
}

void MACounter()
{
  if (!digitalRead(encoderA))
  {
    MATicks++;
  }
  else
  {
    MATicks--;
  }
}

void MBCounter()
{
  if (digitalRead(encoderB))
  {
    MBTicks++;
  }
  else
  {
    MBTicks--;
  }
}

bool getSwitchState(int id) {
  int switchPin;

  if (id == 1) {
    switchPin = switch1Pin;
  }else if (id == 2) {
    switchPin = switch2Pin;
  }else if (id == 3) {
    switchPin = switch3Pin;
  }else if (id == 4) {
    switchPin = switch4Pin;
  }

  return analogRead(switchPin) > 512; // pour retourner une valeur bool on compare avec la valeur médiane sur la plage 0-1023
}
