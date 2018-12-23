#include "ZEROplusMotors.h"

#define ENAB_A_PIN   5     // Motor A
#define DIR_A1_PIN   4     // 
#define DIR_A2_PIN   7     // 
#define ENAB_B_PIN   6     // Motor B
#define DIR_B1_PIN   3     // 
#define DIR_B2_PIN   8     // 

static boolean flipLeft = false;
static boolean flipRight = false;
static int MotorBalance = 0;

// constructor (doesn't do anything)
ZEROplusMotors::ZEROplusMotors()
{
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void ZEROplusMotors::init2()
{
  pinMode(ENAB_A_PIN, OUTPUT);
  pinMode(DIR_A1_PIN, OUTPUT);
  pinMode(DIR_A2_PIN, OUTPUT);
  pinMode(ENAB_B_PIN, OUTPUT);
  pinMode(DIR_B1_PIN, OUTPUT);
  pinMode(DIR_B2_PIN, OUTPUT);
}

void ZEROplusMotors::setMotorBalance(int Speed)
{
	MotorBalance = Speed;
}

// enable/disable flipping of left motor
void ZEROplusMotors::flipLeftMotor(boolean flip)
{
  flipLeft = flip;
}

// enable/disable flipping of right motor
void ZEROplusMotors::flipRightMotor(boolean flip)
{
  flipRight = flip;
}

// set speed for left motor; speed is a number between -400 and 400
void ZEROplusMotors::setLeftSpeed(int speed)
{
  init(); // initialize if necessary
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 255)  // Max 
    speed = 255;
    
  analogWrite(ENAB_B_PIN, speed); // default to using analogWrite, mapping 400 to 255
  if (reverse ^ flipLeft) {           // flip if speed was negative or flipLeft setting is active, but not both
    digitalWrite(DIR_B1_PIN,  LOW);
    digitalWrite(DIR_B2_PIN, HIGH); 
  }
  else {
    digitalWrite(DIR_B1_PIN, HIGH);
    digitalWrite(DIR_B2_PIN,  LOW); 
  }
}

// set speed for right motor; speed is a number between -400 and 400
void ZEROplusMotors::setRightSpeed(int speed)
{
  init(); // initialize if necessary
    
  boolean reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 255)  // Max PWM dutycycle
    speed = 255;

  analogWrite(ENAB_A_PIN, speed); // default to using analogWrite, mapping 400 to 255
  if (reverse ^ flipRight) {             // flip if speed was negative or flipRight setting is active, but not both
    digitalWrite(DIR_A1_PIN, HIGH);
    digitalWrite(DIR_A2_PIN,  LOW); 
  }
  else {
    digitalWrite(DIR_A1_PIN,  LOW);
    digitalWrite(DIR_A2_PIN, HIGH); 
  }
}

// set speed for both motors
void ZEROplusMotors::forward_diff(int leftSpeed, int rightSpeed)
{
  setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
}

void ZEROplusMotors::forward(int Speed)
{
  setLeftSpeed(Speed-MotorBalance);
  setRightSpeed(Speed+MotorBalance);
}

void ZEROplusMotors::forward(int Speed, int Mtime)
{
  setLeftSpeed(Speed-MotorBalance);
  setRightSpeed(Speed+MotorBalance);
  delay(Mtime);
}

void ZEROplusMotors::backward(int Speed)
{
  setLeftSpeed(-Speed+MotorBalance);
  setRightSpeed(-Speed-MotorBalance);
}

void ZEROplusMotors::backward(int Speed, int Mtime)
{
  setLeftSpeed(-Speed);
  setRightSpeed(-Speed);
  delay(Mtime);
}

void ZEROplusMotors::turnRight(int Speed)
{
  setLeftSpeed(Speed);
  setRightSpeed(-Speed);
}

void ZEROplusMotors::turnRight(int Speed, int Mtime)
{
  setLeftSpeed(Speed);
  setRightSpeed(-Speed);
  delay(Mtime);
}

void ZEROplusMotors::turnLeft(int Speed)
{
  setLeftSpeed(-Speed);
  setRightSpeed(Speed);
}

void ZEROplusMotors::turnLeft(int Speed, int Mtime)
{
  setLeftSpeed(-Speed);
  setRightSpeed(Speed);
  delay(Mtime);
}

void ZEROplusMotors::brake(int Mtime)
{
  setLeftSpeed(0);
  setRightSpeed(0);
  delay(Mtime);
}