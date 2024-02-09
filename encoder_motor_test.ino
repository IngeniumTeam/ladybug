#include <Servo.h>

#define LED_PIN 4
#define SERVO_PIN 9

//moteur1_
#define MOT1_PLUS 7
#define MOT1_MOINS 8
#define MOT1_PWM 5
#define MOT1_ENCODER_A 2 // ne pas changer, cette broche a l'interrupt HW
#define MOT1_ENCODER_B A0

//moteur2_
#define MOT2_PLUS 11
#define MOT2_MOINS 12
#define MOT2_PWM 6
#define MOT2_ENCODER_A 3 // ne pas changer, cette broche a l'interrupt HW
#define MOT2_ENCODER_B A1
//STBY
#define STBY_PIN 10
#define LIMIT_SWITCH 13

Servo servo;

volatile long top_counter_mot1;
volatile long top_counter_mot2;

int ticksPerTurn = 353;
int wheelDiameter = 65; // millimetres
int halfVehicleTrack = 57; // millimetres : c'est la demi-voie du robot
int turnCounter = 0;

int ticksDiff = 0;
float coeff = 1.5;
int maxTicks = 5*ticksPerTurn;
int straightDistance = 1500;
int basePWM = 100;

int mot1PWM;
int mot2PWM;

String logMessage;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(STBY_PIN, OUTPUT);

  pinMode(MOT1_PLUS, OUTPUT);
  pinMode(MOT1_MOINS, OUTPUT);
  pinMode(MOT1_PWM, OUTPUT);
  pinMode(MOT2_PWM, OUTPUT);
  pinMode(MOT2_PLUS, OUTPUT);
  pinMode(MOT2_MOINS, OUTPUT);

  pinMode(MOT1_ENCODER_A, INPUT);
  pinMode(MOT1_ENCODER_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(MOT1_ENCODER_A), tic1Detector, RISING);

  pinMode(MOT2_ENCODER_A, INPUT);
  pinMode(MOT2_ENCODER_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(MOT2_ENCODER_A), tic2Detector, RISING);  

  pinMode(LIMIT_SWITCH, INPUT);

  servo.attach(SERVO_PIN);

  blink_LED(3);

  Serial.begin(9600);

  servo.write(100);

  // Déplacement PAMI 1
  // driveStraight(550, true, false);
  // drivePivot(85, true); 

  // Déplacements PAMI 2
  driveStraight(250, true, false);
  drivePivot(90, true); 
  driveStraight(500, true, false);
  drivePivot(90, true); 

  driveStraight(100000, true, true);

  servo.write(300);
}

void loop() {
  // décommenter la fonction qu'on souhaite utiliser
  
  // measureMotorTicks();

  // compareTwoMotors();

  // equalTicksRegulator(maxTicks, 1);

  // blockUntilClick();
  // driveStraight(straightDistance, true);
  // blockUntilClick();
  // drivePivot (180, true);
  // blockUntilClick();
  // driveStraight(straightDistance, false);
  // blockUntilClick();
  // drivePivot (180, false);  

}


void drivePivot(int angle, bool clockwise)
{
  // angle doit etre exprime en degres
    float radAngle = angle * PI / 180.0;
    maxTicks = int(radAngle / (2 * PI) * ticksPerTurn * halfVehicleTrack / wheelDiameter * 2.0);
  Serial.println(maxTicks); 

  if (clockwise)
    equalTicksRegulator(maxTicks, 3, false);
  else
    equalTicksRegulator(maxTicks, 4, false);
}


void driveStraight(int distance, bool forward, bool interruptable)
{
  // distance doit etre exprime en millimetres
    maxTicks = int(distance / PI / wheelDiameter * ticksPerTurn);
    Serial.println(maxTicks); 

    if (forward)
      equalTicksRegulator(maxTicks, 1, interruptable);
    else
      equalTicksRegulator(maxTicks, 2, interruptable);
}


void equalTicksRegulator(int maxTicks, int movement, bool interruptable)
{
  int signMot1;
  int signMot2;
  
  switch(movement)
  {
    case 1: // straight, forward
      signMot1 = 1;
      signMot2 = 1;
    break;
    case 2: // straight, reverse
      signMot1 = -1;
      signMot2 = -1;
    break;
    case 3: // pivot, clockwise
      signMot1 = -1;
      signMot2 = 1;
    break;    
    case 4: // pivot, counter-clockwise
      signMot1 = 1;
      signMot2 = -1;
    break;    
    default:
      signMot1 = 0;
      signMot2 = 0;
    break;
  } 
  
  while (max(abs(top_counter_mot1), abs(top_counter_mot2)) < maxTicks)
  {
    if (interruptable & digitalRead(LIMIT_SWITCH)) {
      delay(500);
      break;
    }

    if (abs(top_counter_mot1) < maxTicks)
    {
      mot1PWM = min(255, basePWM - ticksDiff*coeff);
      moveMotor(1, signMot1 * mot1PWM);
    }    
    if (abs(top_counter_mot2) < maxTicks)
    {
      mot2PWM = min(255, basePWM + ticksDiff*coeff);
      moveMotor(2, signMot2 * mot2PWM);
    }
    
    ticksDiff = abs(top_counter_mot1) - abs(top_counter_mot2);
    //delay(100);
  }

  stopMotor(2);
  stopMotor(1);
  logMessage = "Test number ";
  logMessage += turnCounter; 
  logMessage += " Ticks moteur 1: ";
  logMessage += top_counter_mot1;
  logMessage += " Ticks moteur 2: ";
  logMessage += top_counter_mot2;
  logMessage += " Final mot1 PWM";
  logMessage += mot1PWM;
  logMessage += " Final mot2 PWM";
  logMessage += mot2PWM;
  Serial.println(logMessage);  

  top_counter_mot1 = 0;
  top_counter_mot2 = 0;
  turnCounter++;
  
}

void compareTwoMotors()
{
  while (min(top_counter_mot1, top_counter_mot2) < 2*ticksPerTurn)
  {
    moveMotor(1, 150);
    moveMotor(2, 150);
    //delay(100);
  }

  stopMotor(2);
  stopMotor(1);
  logMessage = "Turn number ";
  logMessage += turnCounter; 
  logMessage += " Ticks moteur 1: ";
  logMessage += top_counter_mot1;
  logMessage += " Ticks moteur 2: ";
  logMessage += top_counter_mot2;
  Serial.println(logMessage);  

  top_counter_mot1 = 0;
  top_counter_mot2 = 0;
  turnCounter++;

  blockUntilClick();
  
}

void measureMotorTicks()
{
  while (true)
  {
    //moveMotor(1, 150);

    Serial.print("Encoder A Moteur 1: ");
    Serial.print(digitalRead(MOT1_ENCODER_A));
    Serial.print(" B Moteur 1: ");
    Serial.print(digitalRead(MOT1_ENCODER_B));
    Serial.print(" A Moteur 2: ");
    Serial.print(digitalRead(MOT2_ENCODER_A));
    Serial.print(" B Moteur 2: ");
    Serial.print(digitalRead(MOT2_ENCODER_B));
    Serial.print(" Tops moteur 1: ");
    Serial.print(top_counter_mot1);    
    Serial.print(" Tops moteur 2: ");
    Serial.println(top_counter_mot2);  

    if(digitalRead(LIMIT_SWITCH))
    {
      top_counter_mot1 = 0;
      top_counter_mot2 = 0;
    }

    delay(100);
  }
}


void blink_LED(int nb_blinks)
{
  int i;
  for (i = 0; i < nb_blinks; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }  
}

void blockUntilClick()
{
  int counter = 0;
  while (!digitalRead(LIMIT_SWITCH))
  {
    counter ++;
    if (counter > 30000)
    {
      counter = 0;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
  }

}

void stopMotor(int motorNumber)
{
  digitalWrite(STBY_PIN, HIGH);
  if(motorNumber == 1)
  {
    digitalWrite(MOT1_PLUS, HIGH);
    digitalWrite(MOT1_MOINS, HIGH);
  }
  else if (motorNumber == 2)
  {
    digitalWrite(MOT2_PLUS, HIGH);
    digitalWrite(MOT2_MOINS, HIGH);
  }
}

void releaseMotor(int motorNumber)
{
  digitalWrite(STBY_PIN, HIGH);
  if(motorNumber == 1)
  {
    digitalWrite(MOT1_PLUS, LOW);
    digitalWrite(MOT1_MOINS, LOW);
  }
  else if (motorNumber == 2)
  {
    digitalWrite(MOT2_PLUS, LOW);
    digitalWrite(MOT2_MOINS, LOW);
  }
}

void moveMotor(int motorNumber, int power)
{
  digitalWrite(STBY_PIN, HIGH);
  if(motorNumber == 1)
  {
    if (power > 0)
    {
      digitalWrite(MOT1_PLUS, HIGH);
      digitalWrite(MOT1_MOINS, LOW);
      analogWrite(MOT1_PWM, power);
    }
    else
    {
      digitalWrite(MOT1_PLUS, LOW);
      digitalWrite(MOT1_MOINS, HIGH);
      analogWrite(MOT1_PWM, -power);      
    }
  }
  else if (motorNumber == 2)
  {
    if (power > 0)
    {
      digitalWrite(MOT2_PLUS, HIGH);
      digitalWrite(MOT2_MOINS, LOW);
      analogWrite(MOT2_PWM, power);
    }
    else
    {
      digitalWrite(MOT2_PLUS, LOW);
      digitalWrite(MOT2_MOINS, HIGH);
      analogWrite(MOT2_PWM, -power);      
    }
  }
}

void tic1Detector()
{
  if (!digitalRead(MOT1_ENCODER_B))
  {
    top_counter_mot1++;
  }
  else
  {
    top_counter_mot1--;
  }
}

void tic2Detector()
{
  if (digitalRead(MOT2_ENCODER_B))
  {
    top_counter_mot2++;
  }
  else
  {
    top_counter_mot2--;
  }
}
