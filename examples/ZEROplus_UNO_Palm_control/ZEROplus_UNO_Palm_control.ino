#include <ZEROplus_Robot.h>     // Line tracing library
#include "pins.h"
#include "Configuration.h"
#include "pitches.h"

///////////////// QTR SENSORS VARIABLES /////////////////////////////////////////////////////////
#define NUM_SENSORS             3          // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4          // average 4 analog samples per sensor reading
#define EMITTER_PIN    QTR_NO_EMITTER_PIN  // emitter is controlled by no pin (digital pin 2)
QTRSensorsAnalog qtra((unsigned char[]) {QTR2_PIN,QTR3_PIN,QTR4_PIN}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
unsigned int sensorValue_L ;     
unsigned int sensorValue_R ;
int lastError = 0;

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
int  counter_motor_forward_loop = 0;
int  index_which_QTR_detected   = 2;  // 0,1,2,3,4  2 is middle
boolean STATUS_Motor_disabled   = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(BATT_READ_PIN, INPUT);    
  pinMode(POWER_LED_PIN,OUTPUT); 
  pinMode(SOUND_BUZZER_PIN,OUTPUT);
  pinMode(MODE_SELECT_PIN,  INPUT);
  
  motors.setMotorBalance(MOTOR_BALANCE);      // + value to the left side, - value to the right side
  motors.flipLeftMotor (true);                // robot in upside down position
  motors.flipRightMotor(true);                // robot in upside down position
  
  digitalWrite(POWER_LED_PIN,HIGH);
  playsong_poweron();
   
  Serial.begin(57600);  
  delay(300);
}

void loop() {
  DEBUG_Serial_monitor(200);
  if(Power_Management() == 0 || STATUS_Motor_disabled) { motors.brake(10); return; }

  Palm_control_Move();
}
