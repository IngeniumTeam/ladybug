#include "HardwareSerial.h"
#include "PAMI_Interface.h"

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

  int maxTicks = int(radAngle / PI * ticksPerTurn * halfVehicleTrack / wheelDiameter);
  //Serial.println(maxTicks); 

  if (clockwise)
    equalTicksRegulator(maxTicks, 3, false);
  else
    equalTicksRegulator(maxTicks, 4, false);
}

void PAMI_Interface::driveStraight(int distance, bool forward, bool interruptable)
{
  // distance doit etre exprime en millimetres
  int maxTicks = int(distance / PI / wheelDiameter * ticksPerTurn);

  if (forward)
    equalTicksRegulator(maxTicks, 1, interruptable);
  else
    equalTicksRegulator(maxTicks, 2, interruptable);
}

void PAMI_Interface::equalTicksRegulator(int maxTicks, int movement, bool interruptable)
{
  int basePWM_mot;
  int basePWM = 100;

  int signMot1;
  int signMot2;
  
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
      signMot1 = 1;
      signMot2 = -1;
      basePWM = pivotPWM;
    break;    
    case 4: // pivot, counter-clockwise
      signMot1 = -1;
      signMot2 = 1;
      basePWM = pivotPWM;
    break;    
    default:
      signMot1 = 0;
      signMot2 = 0;
    break;
  } 
  
  while (max(abs(MATicks), abs(MBTicks)) < maxTicks)
  {
    timeout.loop();
    if (abs(MATicks) > (maxTicks - ticksForAccel) ) // un certain nombre de ticks avant d'avoir terminé le mouvement
    {
      basePWM_mot = minPWM + ( (basePWM - minPWM) * (maxTicks - abs(MATicks) ) / ticksForAccel) ;
    }

    else if(abs(MATicks) < ticksForAccel) // au début du mouvement
    {
      basePWM_mot = minPWM + ( (basePWM - minPWM) * abs(MATicks) ) / ticksForAccel ;
    }
    else
    {
      basePWM_mot = basePWM;
    }
      

    // commander les moteurs jusqu'à ce qu'on ait atteint le nombre de ticks désiré
    mot1PWM = min(255, basePWM_mot - ticksDiff*coeff);
    mot2PWM = min(255, basePWM_mot + ticksDiff*coeff);
    // Serial.println("PWM " + String(basePWM_mot));
    moveMotors(signMot1 * mot1PWM, signMot2 * mot2PWM);
    
    ticksDiff = abs(MATicks) - abs(MBTicks);
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
  Serial.println("MATicks : " + String(MATicks) + "MBTicks : " + String(MBTicks) + "MaxTicks : " + String(maxTicks));
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