#include <ZEROplus_Robot.h>
#include "pins.h"
#include "Configuration.h"
#include "pitches.h"

///////////////// QTR SENSORS VARIABLES //////////////////////////////////////////////////////////
#define NUM_SENSORS             3          // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4          // average 4 analog samples per sensor reading
#define EMITTER_PIN    QTR_NO_EMITTER_PIN  // emitter is controlled by no pin (digital pin 2)
QTRSensorsAnalog qtra((unsigned char[]) {QTR2_PIN,QTR3_PIN,QTR4_PIN}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
unsigned int sensorValue_L ;     
unsigned int sensorValue_R ;
int lastError = 0;

///////////////// Motor VARIABLES /////////////////////////////////////////////////////////////////
ZEROplusMotors motors;
long index_Motor_startTime = 0;  
int MotorBalance = MOTOR_BALANCE;


///////////////// LEDs (Power,Lower) VARIABLES ////////////////////////////////////////////////////
long index_Power_LED_startTime = 0;  int  state_Power_LED = LOW;  
long index_Serial_startTime = 0;

///////////////// Ultrasonic VARIABLES ////////////////////////////////////////////////////////////
NewPing sonar(TRIG_PIN, ECHO_PIN, 400);
int  read_sonar_cm = 10;
long ping_duration = 1000;

///////////////// Buzzer VARIABLES ////////////////////////////////////////////////////////////////
int  melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int  noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};  // note durations: 4 = quarter note, 8 = eighth note
long index_Buzzer_startTime = 0;

///////////////// Battery (Voltage divider) VARIABLES /////////////////////////////////////////////
// max Vin : 5.5~6V(4*AA), analogRead(adc)*5000*3/2/1023 = value of batt mV 
const float resistorFactor = 5000*3/2/1023; // 7.3314
int  COUNT_batt_volt = 1;             // for averging batt shutdown volt
int  LED_interval = NO_BLINK;    
int  read_batt_volt =  0;

///////////////// GLOBAL and ETC VARIABLES ////////////////////////////////////////////////////////
int  loopTime  = 1 ;                   // every 0.001sec for looping (basic loop time)
int  counter_motor_forward_loop = 0;
long COUNT_for_square_cross     = 0;
long COUNT_for_line_interrupt   = 0;
int  index_which_QTR_detected   = 2;  // 0,1,2,3,4  2 is middle

///////////////// GLOBAL Switch VARIABLES /////////////////////////////////////////////////////////
boolean STATUS_black_found       = false;   // could be Black-line or Cliff
boolean STATUS_Calibration_setup = false;
boolean STATUS_square_found      = false;
boolean STATUS_Motor_disabled    = false;
boolean STATUS_Sonar_disabled    = false;
boolean Switch_line_follow_mode  = true; 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  //// pinmode definition////////////////////////
  ///////////////////////////////////////////////
  pinMode(BATT_READ_PIN, INPUT);    
  pinMode(POWER_LED_PIN,OUTPUT); 
  pinMode(SOUND_BUZZER_PIN,OUTPUT);
  pinMode(MODE_SELECT_PIN,  INPUT);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  motors.setMotorBalance(MOTOR_BALANCE);
  if(sonar.ping_cm() == 0) STATUS_Sonar_disabled = true;       // sonar uninstalled
  if(digitalRead(MODE_SELECT_PIN) == HIGH) Switch_line_follow_mode = false;      // mode select pin
  digitalWrite(POWER_LED_PIN,HIGH);
  
  playsong_poweron();
   
  Serial.begin(9600);  
  delay(300);
}

void loop() {
  DEBUG_Serial_monitor(200);
  if(Power_Management() == 0 || STATUS_Motor_disabled) { motors.brake(10); return; }

  if(Switch_line_follow_mode) {
    if(STATUS_black_found) Line_Follow_Move();
    else{
      if(Check_Darkness_inFloor()) { motors.forward(LTRspeed,GAP_time); STATUS_black_found = true; }
      motors.forward (RUNspeed);
    }
  }
  else{
    STATUS_black_found = false;
    Autonomous_Move();
  }
//Serial.print(" *findDistance : "); Serial.print(sonar.ping_cm()); Serial.println("  ");
//delay(1000);
}

int Check_Darkness_inFloor() {    // if analogRead is over 950 for a while
  qtra.read(sensorValues);  // sensorValues[0],sensorValues[1],sensorValues[2]
  if (sensorValues[0] < 150) return 1;
  if (sensorValues[1] < 150) return 2;
  if (sensorValues[2] < 150) return 3;
  return 0;
}

int scan_average_cm(int num) {
  ping_duration = sonar.ping_median(num);
  return (int)(ping_duration/2)*0.0343;
}

