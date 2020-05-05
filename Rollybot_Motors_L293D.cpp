#include "Rollybot_Motors_L293D.h"

static  boolean flipLeft  = false;
static  boolean flipRight = false;
static int MotorBalance = 0;
uint8_t enab_a_pin;
uint8_t dir_a1_pin;
uint8_t dir_a2_pin;
uint8_t enab_b_pin;
uint8_t dir_b1_pin;
uint8_t dir_b2_pin;

// constructor (doesn't do anything)
Rollybot_Motors_L293D::Rollybot_Motors_L293D(uint8_t _enab_a, uint8_t _dir_a1, uint8_t _dir_a2, uint8_t _enab_b, uint8_t _dir_b1, uint8_t _dir_b2)
{
  enab_a_pin = _enab_a ;    // Motor A (Right motor)
  dir_a1_pin = _dir_a1 ;    // 
  dir_a2_pin = _dir_a2 ;    //
  enab_b_pin = _enab_b ;    // Motor B (Left motor)
  dir_b1_pin = _dir_b1 ;    //
  dir_b2_pin = _dir_b2 ;    //
}

// initialize timer1 to generate the proper PWM outputs to the motor drivers
void Rollybot_Motors_L293D::init2()
{
  pinMode(enab_a_pin, OUTPUT);
  pinMode(dir_a1_pin, OUTPUT);
  pinMode(dir_a2_pin, OUTPUT);
  pinMode(enab_b_pin, OUTPUT);
  pinMode(dir_b1_pin, OUTPUT);
  pinMode(dir_b2_pin, OUTPUT);
}

void Rollybot_Motors_L293D::setMotorBalance(int Speed)
{
	MotorBalance = Speed;
}

// enable/disable flipping of left motor
void Rollybot_Motors_L293D::flipLeftMotor(boolean flip)
{
  flipLeft = flip;
}

// enable/disable flipping of right motor
void Rollybot_Motors_L293D::flipRightMotor(boolean flip)
{
  flipRight = flip;
}

// set speed for left motor; speed is a number between -400 and 400
void Rollybot_Motors_L293D::setLeftSpeed(int speed)
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
    
  analogWrite(enab_b_pin, speed); // default to using analogWrite, mapping 400 to 255
  if (reverse ^ flipLeft) {           // flip if speed was negative or flipLeft setting is active, but not both
    digitalWrite(dir_b1_pin,  LOW);
    digitalWrite(dir_b2_pin, HIGH); 
  }
  else {
    digitalWrite(dir_b1_pin, HIGH);
    digitalWrite(dir_b2_pin,  LOW); 
  }
}

// set speed for right motor; speed is a number between -400 and 400
void Rollybot_Motors_L293D::setRightSpeed(int speed)
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

  analogWrite(enab_a_pin, speed); // default to using analogWrite, mapping 400 to 255
  if (reverse ^ flipRight) {             // flip if speed was negative or flipRight setting is active, but not both
    digitalWrite(dir_a1_pin, HIGH);
    digitalWrite(dir_a2_pin,  LOW); 
  }
  else {
    digitalWrite(dir_a1_pin,  LOW);
    digitalWrite(dir_a2_pin, HIGH); 
  }
}

// set speed for both motors
void Rollybot_Motors_L293D::forward_diff(int leftSpeed, int rightSpeed)
{
  setLeftSpeed(leftSpeed);
  setRightSpeed(rightSpeed);
}

void Rollybot_Motors_L293D::forward(int Speed)
{
  setLeftSpeed(Speed-MotorBalance);
  setRightSpeed(Speed+MotorBalance);
}

void Rollybot_Motors_L293D::forward(int Speed, int Mtime)
{
  setLeftSpeed(Speed-MotorBalance);
  setRightSpeed(Speed+MotorBalance);
  delay(Mtime);
}

void Rollybot_Motors_L293D::backward(int Speed)
{
  setLeftSpeed(-Speed+MotorBalance);
  setRightSpeed(-Speed-MotorBalance);
}

void Rollybot_Motors_L293D::backward(int Speed, int Mtime)
{
  setLeftSpeed(-Speed);
  setRightSpeed(-Speed);
  delay(Mtime);
}

void Rollybot_Motors_L293D::turnRight(int Speed)
{
  setLeftSpeed(Speed);
  setRightSpeed(-Speed);
}

void Rollybot_Motors_L293D::turnRight(int Speed, int Mtime)
{
  setLeftSpeed(Speed);
  setRightSpeed(-Speed);
  delay(Mtime);
}

void Rollybot_Motors_L293D::turnLeft(int Speed)
{
  setLeftSpeed(-Speed);
  setRightSpeed(Speed);
}

void Rollybot_Motors_L293D::turnLeft(int Speed, int Mtime)
{
  setLeftSpeed(-Speed);
  setRightSpeed(Speed);
  delay(Mtime);
}

void Rollybot_Motors_L293D::brake(int Mtime)
{
  setLeftSpeed(0);
  setRightSpeed(0);
  delay(Mtime);
}