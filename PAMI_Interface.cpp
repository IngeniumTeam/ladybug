#include "PAMI_Interface.h"

Servo armMotor;

motorStates MALastState = motorStates::Stop;
motorStates MBLastState = motorStates::Stop;
int currentSpeed = 0;

double consigne = 0;
double outputMotorA, outputMotorB;
double Kp = 5.0, Ki = 0.0, Kd = 0.0;
double MATicksDouble;
double MBTicksDouble;

PID pidMotorA(&MATicksDouble, &outputMotorA, &consigne, Kp, Ki, Kd, DIRECT);
PID pidMotorB(&MBTicksDouble, &outputMotorB, &consigne, Kp, Ki, Kd, DIRECT);

void PAMIInterface::setup() {
  setupMotors();
  setupEncoder(355, 385);
  armMotor.attach(servoArmPin);
  pinMode(limitSwitchPin, INPUT);
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch3Pin, INPUT);
  pinMode(switch4Pin, INPUT);
  
  pinMode(ledPin, OUTPUT);

  pidMotorA.SetMode(AUTOMATIC);
  pidMotorB.SetMode(AUTOMATIC);

  // armMotor.write(180);
}

void PAMIInterface::controlMotors(PAMIInterface::motorsDirections direction, PAMIInterface::motorsSpeeds speed = PAMIInterface::motorsSpeeds::Three) {
  bool correctDirection = false;

  if(direction == PAMIInterface::motorsDirections::Forwards){
    MALastState = motorStates::Forward;
    MBLastState = motorStates::Forward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Backwards){
    MALastState = motorStates::Backward;
    MBLastState = motorStates::Backward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Lefts){
    MALastState = motorStates::Forward;
    MBLastState = motorStates::Backward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Rights){
    MALastState = motorStates::Backward;
    MBLastState = motorStates::Forward;
    correctDirection = true;
  }else if(direction == PAMIInterface::motorsDirections::Stops){
    MALastState = motorStates::Stop;
    MBLastState = motorStates::Stop;
    correctDirection = true;
  }

  if(correctDirection) {
    moveMotors(MALastState, MBLastState, speed, speed);
    currentSpeed = speed;
  }
}

void PAMIInterface::raiseArm() {
  armMotor.write(70);
}

void PAMIInterface::lowerArm() {
  armMotor.write(30);
}

bool PAMIInterface::getLimitSwitchState() {
  return digitalRead(limitSwitchPin);
}

bool PAMIInterface::getSwitchState(int id) {
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

  return analogRead(switchPin);
}

void PAMIInterface::setLedState(bool ledState) {
  digitalWrite(ledPin, ledState);
}

static void PAMIInterface::fixMotors(int coef) {
  // MATicksDouble = static_cast<double>(MATicks);
  // MBTicksDouble = static_cast<double>(MBTicks);
  int diff = MATicks - MBTicks;
  int MASpeed = constrain(currentSpeed - coef * diff, 0, 255);
  int MBSpeed = constrain(currentSpeed + coef * diff, 0, 255);

  Serial.println("A : " + String(MATicks) + " B : " + String(MBTicks) + " Diff : " + diff);
  // pidMotorA.Compute();
  // pidMotorB.Compute();

  // moveMotors(MALastState, MBLastState, MASpeed, MBSpeed);

}
