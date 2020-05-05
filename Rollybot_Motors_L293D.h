
#ifndef Rollybot_Motors_L293D_h
#define Rollybot_Motors_L293D_h

#include <Arduino.h>

class Rollybot_Motors_L293D
{
  public:  
  
    // constructor (doesn't do anything)
    Rollybot_Motors_L293D(uint8_t enab_a, uint8_t dir_a1, uint8_t dir_a2, uint8_t enab_b, uint8_t dir_b1, uint8_t dir_b2);
    
    // enable/disable flipping of motors
    static void flipLeftMotor(boolean flip);
    static void flipRightMotor(boolean flip);
	static void setMotorBalance(int Speed);
    
    // set speed for left, right, or both motors
    static void setLeftSpeed (int speed);
    static void setRightSpeed(int speed);
    static void forward_diff (int leftSpeed, int rightSpeed);
	static void forward(int Speed);
	static void forward(int Speed, int Mtime);
	static void backward(int Speed);
	static void backward(int Speed, int Mtime);
	static void turnRight(int Speed);
	static void turnRight(int Speed, int Mtime);
	static void turnLeft(int Speed);
	static void turnLeft(int Speed, int Mtime);
	static void brake(int Mtime);
    
  private:

    static inline void init()
    {
      static boolean initialized = false;

      if (!initialized)
      {
        initialized = true;
        init2();
      }
    }
    
    // initializes timer1 for proper PWM generation
    static void init2();
};

#endif