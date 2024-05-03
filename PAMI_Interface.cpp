#include "HardwareSerial.h"
#include "PAMI_Interface.h"
//#include "Timeout.h"

Servo armMotor;

PAMI_Interface::PAMI_Interface()
{
  
}

void PAMI_Interface::PAMIsetup() {
  pinMode(aIn1, OUTPUT);
  pinMode(aIn2, OUTPUT);
  pinMode(bIn1, OUTPUT);
  pinMode(bIn2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);

  pinMode(STBY,OUTPUT);
  digitalWrite(STBY, HIGH);

  pinMode(limitSwitchPin, INPUT);
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);
  
  pinMode(ledPin, OUTPUT);

  armMotor.attach(servoArmPin);
  armMotor.write(180);
}


void PAMI_Interface::raiseArm() {
  armMotor.write(70);
}

void PAMI_Interface::lowerArm() {
  armMotor.write(300);
}

bool PAMI_Interface::getLimitSwitchState() {
  return digitalRead(limitSwitchPin);
}

bool PAMI_Interface::getSwitchState(int id) {
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

  return (analogRead(switchPin) > 512); // pour retourner une valeur bool on compare avec la valeur médiane sur la plage 0-1023
}

void PAMI_Interface::setLedState(bool ledState) {
  digitalWrite(ledPin, ledState);
}

void PAMI_Interface::stopMotors()
{
  digitalWrite(aIn1, HIGH);
  digitalWrite(aIn2, HIGH);
  analogWrite(pwmA, 0);
  digitalWrite(bIn1, HIGH);
  digitalWrite(bIn2, HIGH);
  analogWrite(pwmB, 0);
}

void PAMI_Interface::moveMotors(int power_motor1, int power_motor2)
{
  if (power_motor1 > 0)
  {
    digitalWrite(aIn1, HIGH);
    digitalWrite(aIn2, LOW);
    analogWrite(pwmA, power_motor1);
  }
  else
  {
    digitalWrite(aIn1, LOW);
    digitalWrite(aIn2, HIGH);
    analogWrite(pwmA, -power_motor1);      
  }

  if (power_motor2 > 0)
  {
    digitalWrite(bIn1, HIGH);
    digitalWrite(bIn2, LOW);
    analogWrite(pwmB, power_motor2);
  }
  else
  {
    digitalWrite(bIn1, LOW);
    digitalWrite(bIn2, HIGH);
    analogWrite(pwmB, -power_motor2);      
  }

}

void PAMI_Interface::drivePivot(int angle, bool clockwise)
{
  // angle doit etre exprime en degres
  float radAngle = 0;
  
  if (clockwise)
    radAngle = (angle * correctCW) * PI / 180.0;
  else
    radAngle = (angle * correctCCW) * PI / 180.0;

  int distance = int(radAngle * halfVehicleTrack);
  // int maxTicks = int(radAngle / PI * ticksPerTurn * halfVehicleTrack / wheelDiameter);
  // Serial.println(radAngle);
  //Serial.println(maxTicks); 

  if (!clockwise)
    equalDistRegulator(distance - extraDist, 3, false);
  else
    equalDistRegulator(distance - extraDist, 4, false);
}

void PAMI_Interface::driveStraight(int distance, bool forward, bool interruptable)
{
  // distance doit etre exprime en millimetres

  if (forward)
    equalDistRegulator(distance - extraDist, 1, interruptable);
  else
    equalDistRegulator(distance - extraDist, 2, interruptable);
}

void PAMI_Interface::equalDistRegulator(int distance, int movement, bool interruptable)
{
  int basePWM_mot;
  int basePWM = 100;

  int signMot1;
  int signMot2;
  
  float distance_A = 0.0;
  float distance_B = 0.0;
  distanceDiff = abs(distance_A) - abs(distance_B);

  switch(movement)
  {
    case 1: // straight, forward
      signMot1 = 1;
      signMot2 = 1;
      basePWM = straightPWM;
    break;
    case 2: // straight, reverse
      signMot1 = -1;
      signMot2 = -1;
      basePWM = straightPWM;
    break;
    case 3: // pivot, clockwise
      signMot1 = -1;
      signMot2 = 1;
      basePWM = pivotPWM;
    break;    
    case 4: // pivot, counter-clockwise
      signMot1 = 1;
      signMot2 = -1;
      basePWM = pivotPWM;
    break;    
    default:
      signMot1 = 0;
      signMot2 = 0;
    break;
  } 

  // commander les moteurs jusqu'à ce qu'on ait atteint le nombre de ticks désiré
  while (max(abs(distance_A), abs(distance_B)) < distance)
  {
    distance_A = MATicks * PI * wheelDiameter_motA / ticksPerTurn_motA;
    distance_B = MBTicks * PI * wheelDiameter_motB / ticksPerTurn_motB;

    timeout.loop();
    if (abs(distance_A) > (distance - distanceAccel) ) // un certain nombre de ticks avant d'avoir terminé le mouvement
    {
      basePWM_mot = minPWM + ( (basePWM - minPWM) * (distance - abs(distance_A) ) / distanceAccel) ;
    }

    else if(abs(distance_A) < distanceAccel) // au début du mouvement
    {
      basePWM_mot = minPWM + ( (basePWM - minPWM) * abs(distance_A) ) / distanceAccel ;
    }
    else
    {
      basePWM_mot = basePWM;
    }
      
    // Ajuster la puissance des moteurs, si une roue tourne plus vite que l'autre
    if (distanceDiff > 0)
    {
      mot1PWM = max(minMotorDrive, basePWM_mot - distanceDiff*coeff);
      mot2PWM = basePWM_mot;
    }
    else
    {
      mot1PWM = basePWM_mot;
      mot2PWM = max(minMotorDrive, basePWM_mot + distanceDiff*coeff);
    }

    Serial.println("MATicks " + String(MATicks) + ", MBTicks " + String(MBTicks) + ", diff " + String(ticksDiff) + "distance A " + String(distance_A) + ", distance_B " + String(distance_B) + ", diff " + String(distanceDiff) + ", PWM1 " + String(mot1PWM) + ", PWM2 " + String(mot2PWM));
    
    // Commander les moteurs
    moveMotors(signMot1 * mot1PWM, signMot2 * mot2PWM);
    
    // Evaluer la différence entre les deux roues
    ticksDiff = abs(MATicks) - abs(MBTicks);
    distanceDiff = abs(distance_A) - abs(distance_B);
  }

  stopMotors();

  logMessage += " Ticks moteur 1: ";
  logMessage += MATicks;
  logMessage += " Ticks moteur 2: ";
  logMessage += MBTicks;
  logMessage += " Final mot1 PWM";
  logMessage += mot1PWM;
  logMessage += " Final mot2 PWM";
  logMessage += mot2PWM;
  // Serial.println(logMessage);  
  Serial.println("MATicks : " + String(MATicks) + "MBTicks : " + String(MBTicks) + "distance A " + String(distance_A) + ", distance_B " + String(distance_B));
  resetCounterA();
  resetCounterB();
  
}

void PAMI_Interface::resetCounterA()
{
  MATicks = 0;
}

void PAMI_Interface::resetCounterB()
{
  MBTicks = 0;
}

void PAMI_Interface::showTicks()
{
  Serial.print("MATicks: ");
  Serial.print(MATicks);
  Serial.print(" MBTicks: ");
  Serial.println(MBTicks);  
}