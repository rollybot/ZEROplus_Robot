#include <ZEROplus_Robot.h>

#define BATT_READ_PIN     A0     // analog 0 for batt check, max Vin : 15V(3cell lipo), R2/(R1+R2) 
#define POWER_LED_PIN     13     // body vibration (PWM) can use analogWrite()  

ZEROplusMotors motors;
boolean STATUS_Motor_disabled = false;

void setup() {
  pinMode(BATT_READ_PIN, INPUT);
  pinMode(POWER_LED_PIN,OUTPUT);    
  motors.setMotorBalance(0);      // + value to the left side, - value to the right side
}

void loop() {
  if(Power_Management() == 0 || STATUS_Motor_disabled) { motors.brake(10); return; }  // when Low batt volt or USB connection
  
  motors.forward (100);  // speed(0~255)
  delay(500);
  motors.brake(1000);    //ms
  motors.backward(100);  // speed(0~255)
  delay(500);
  motors.brake(1000);    //ms
}
