////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//// ZEROplus Robot Motor control (L293D)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ZEROplus Robot PCB Pinout
/////////////////////////////////////////////////////////////////////////
// ENAB_A_PIN        5     // Motor A
// DIR_A1_PIN        4     // 
// DIR_A2_PIN        7     // 
// ENAB_B_PIN        6     // Motor B
// DIR_B1_PIN        3     // 
// DIR_B2_PIN        8     // 


// Functions   variables { speed(0~255), delay time(milisecond) }
/////////////////////////////////////////////////////////////////////////
// motors.forward(speed,delay time) or motors.forward(speed)
// motors.backward(speed,delay time) or motors.backward(speed)
// motors.turnRight(speed,delay time) or motors.turnRight(speed)
// motors.turnLeft(speed,delay time) or motors.turnLeft(speed)
// motors.brake(ms)
// motors.forward_diff(Left Motor speed, Right Motor speed)
// motors.setMotorBalance(int)
// motors.flipRightMotor(boolean)
// motors.flipLeftMotor(boolean)
