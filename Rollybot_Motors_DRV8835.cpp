#include "Rollybot_Motors_DRV8835.h"

static boolean flipLeft = false;
static boolean flipRight = false;
static int MotorBalance = 0;
uint8_t ENAB_A_PIN;
uint8_t DIR_A1_PIN;
uint8_t ENAB_B_PIN;
uint8_t DIR_B1_PIN;

// constructor (doesn't do anything)
Rollybot_Motors_DRV8835::Rollybot_Motors_DRV8835(uint8_t _enab_a, uint8_t _dir_a, uint8_t _enab_b, uint8_t _dir_b)
{
  ENAB_A_PIN = _enab_a ;    // Motor A
  DIR_A1_PIN =  _dir_a ;    // 
  ENAB_B_PIN = _enab_b ;    // Motor B
  DIR_B1_PIN =  _dir_b ;    //  
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void Rollybot_Motors_DRV8835::init2()
{
  pinMode(ENAB_A_PIN, OUTPUT);
  pinMode(DIR_A1_PIN, OUTPUT);
  pinMode(ENAB_B_PIN, OUTPUT);
  pinMode(DIR_B1_PIN, OUTPUT);
}

void Rollybot_Motors_DRV8835::setMotorBalance(int Speed)
{
	MotorBalance = Speed;
}

// enable/disable flipping of left motor
void Rollybot_Motors_DRV8835::flipLeftMotor(boolean flip)
{
  flipLeft = flip;
}

// enable/disable flipping of right motor
void Rollybot_Motors_DRV8835::flipRightMotor(boolean flip)
{
  flipRight = flip;
}

// set speed for left motor; speed is a number between -400 and 400
void Rollybot_Motors_DRV8835::setLeftSpeed(int speed)
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
    digitalWrite(DIR_B1_PIN, HIGH);
  }
  else {
    digitalWrite(DIR_B1_PIN, LOW); 
  }
}

// set speed for right motor; speed is a number between -400 and 400
void Rollybot_Motors_DRV8835::setRightSpeed(int speed)
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
    digitalWrite(DIR_A1_PIN, LOW); 
  }
  else {
    digitalWrite(DIR_A1_PIN, HIGH); 
  }
}

// set speed for both motors
void Rollybot_Motors_DRV8835::forward_diff(int leftSpeed, int rightSpeed)
{
  setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
}

void Rollybot_Motors_DRV8835::forward(int Speed)
{
  setLeftSpeed(Speed-MotorBalance);
  setRightSpeed(Speed+MotorBalance);
}

void Rollybot_Motors_DRV8835::forward(int Speed, int Mtime)
{
  setLeftSpeed(Speed-MotorBalance);
  setRightSpeed(Speed+MotorBalance);
  delay(Mtime);
}

void Rollybot_Motors_DRV8835::backward_diff(int leftSpeed, int rightSpeed)
{
  setLeftSpeed(-leftSpeed);
  setRightSpeed(-rightSpeed);
}

void Rollybot_Motors_DRV8835::backward(int Speed)
{
  setLeftSpeed(-Speed+MotorBalance);
  setRightSpeed(-Speed-MotorBalance);
}

void Rollybot_Motors_DRV8835::backward(int Speed, int Mtime)
{
  setLeftSpeed(-Speed);
  setRightSpeed(-Speed);
  delay(Mtime);
}

void Rollybot_Motors_DRV8835::turnRight(int Speed)
{
  setLeftSpeed(Speed);
  setRightSpeed(-Speed);
}

void Rollybot_Motors_DRV8835::turnRight(int Speed, int Mtime)
{
  setLeftSpeed(Speed);
  setRightSpeed(-Speed);
  delay(Mtime);
}

void Rollybot_Motors_DRV8835::turnLeft(int Speed)
{
  setLeftSpeed(-Speed);
  setRightSpeed(Speed);
}

void Rollybot_Motors_DRV8835::turnLeft(int Speed, int Mtime)
{
  setLeftSpeed(-Speed);
  setRightSpeed(Speed);
  delay(Mtime);
}

void Rollybot_Motors_DRV8835::brake(int Mtime)
{
  setLeftSpeed(0);
  setRightSpeed(0);
  delay(Mtime);
}