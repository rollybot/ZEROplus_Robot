#include <ZEROplus_Robot.h>     // Line tracing library
#include "pins.h"
#include "Configuration.h"
#include "pitches.h"


///////////////// Motor VARIABLES ////////////////////////////////////////////////////////////////
ZEROplusMotors motors;
long index_Motor_startTime = 0;  
int MotorBalance = MOTOR_BALANCE; 


///////////////// LEDs (Power,Lower) VARIABLES ////////////////////////////////////////////////////
long index_Power_LED_startTime = 0;  int  state_Power_LED = LOW;   
long index_Serial_startTime = 0;


///////////////// Buzzer VARIABLES ////////////////////////////////////////////////////////////////
int  melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int  noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};  // note durations: 4 = quarter note, 8 = eighth note
long index_Buzzer_startTime = 0;

///////////////// Battery (Voltage divider) VARIABLES /////////////////////////////////////////////
// max Vin : 5.5~6V(4*AA), analogRead(adc)*5000*3/2/1023 = value of batt mV 
const float resistorFactor = 5000*3/2/1023; // 7.3314
int COUNT_batt_volt = 1;             // for averging batt shutdown volt
int LED_interval = NO_BLINK;    
int temp_batt_volt =  0;

///////////////// GLOBAL and ETC VARIABLES ////////////////////////////////////////////////////////
boolean STATUS_Motor_disabled   = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(BATT_READ_PIN, INPUT);    
  pinMode(POWER_LED_PIN,OUTPUT); 
  pinMode(SOUND_BUZZER_PIN,OUTPUT);
  pinMode(MODE_SELECT_PIN,  INPUT);
  
  motors.setMotorBalance(MOTOR_BALANCE);      // + value to the left side, - value to the right side
  playsong_poweron();
   
  Serial.begin(9600);  
  delay(300);
}

void loop() {
  DEBUG_Serial_monitor(200);
  if(Power_Management() == 0 || STATUS_Motor_disabled) { motors.brake(10); return; }
  while (!Serial) { motors.brake(1);} // not connect serial port
  if (Serial.available() > 0) {       // Listen for signal in the serial port
    int data = Serial.read(); 
    switch (data) {                    // Switch-case of the signals in the serial port
      case '1': // Case Number 1 is received, 
        motors.forward (100);  break;
      case '2' : //// Case Number 2 is received, 
        motors.backward(100);  break;
      case '3' : // Case Number 3 is received, 
        motors.turnLeft (100); break;
      case '4' : // Case Number 4 is received, 
        motors.turnRight(100);  break;
      case '5': // Case Number 5 is received, 
        motors.brake(1);
      default : break; }
  }
}
