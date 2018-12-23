/*! \file ZumoMotors.h
 *
 * See the ZumoMotors class reference for more information about this library.
 *
 * \class ZumoMotors ZumoMotors.h
 * \brief Control motor speed and direction
 * 
 */

#ifndef ZEROplusMotors_h
#define ZEROplusMotors_h

#include <Arduino.h>

class ZEROplusMotors
{
  public:  
  
    // constructor (doesn't do anything)
    ZEROplusMotors();
    
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