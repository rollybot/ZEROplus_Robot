// example / ZEROplus_UNO_Robot 의 개발자버젼 -> copy to Library/ZEROplus_Robot, when distribute 
// ZEROplus로봇의 메인프로그램 (라인트레이싱/자율주행)


#include <Rollybot_Motors_L293D.h>   // motor control
#include <QTRSensors.h>              // line tracing sensors
#include <Adafruit_SSD1306.h>        // OLED display
#include <NewPing.h>                 // ultrasonic sensor control
#include <NewTone.h>                 // buzzer control

#include "pins.h"                    // pin mapping
#include "Configuration.h"           // input setting values (users can modify this values!!) ,여기서 설정값을 수정하세요
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
Rollybot_Motors_L293D motors(ENAB_A_PIN, DIR_A1_PIN, DIR_A2_PIN, ENAB_B_PIN, DIR_B1_PIN, DIR_B2_PIN);
long index_Motor_startTime = 0;  
int MotorBalance = MOTOR_BALANCE;

///////////////// SSD1306 I2C(OLED) VARIABLES ////////////////////////////////////////////////////
#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
      
///////////////// LEDs (Power,Lower) VARIABLES ////////////////////////////////////////////////////
long index_Power_LED_startTime = 0;  int state_Power_LED = LOW;  
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
const float referenceVolts = 5;
int  COUNT_batt_volt = 1;             // for averging batt shutdown volt
int  LED_interval = NO_BLINK;    
int  read_batt_volt = 0;

///////////////// GLOBAL and ETC VARIABLES ////////////////////////////////////////////////////////
int  loopTime = 1 ;                   // every 0.001sec for looping (basic loop time)
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
  pinMode(BATT_READ_PIN,  INPUT);   
  pinMode(MODE_SELECT_PIN,INPUT); 
  pinMode(POWER_LED_PIN,   OUTPUT); 
  pinMode(SOUND_BUZZER_PIN,OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();
  
  motors.setMotorBalance(MOTOR_BALANCE);
  motors.brake(10);
  
  if(sonar.ping_cm() == 0) STATUS_Sonar_disabled = true;       // sonar uninstalled
  if(digitalRead(MODE_SELECT_PIN) == HIGH) Switch_line_follow_mode = false;      // mode select pin
  digitalWrite(POWER_LED_PIN,HIGH);
  
  playsong_poweron();
  Show_LCD_display();
   
  Serial.begin(9600);  
  delay(300);
}

void loop() {
  //DEBUG_Serial_monitor(500);
  if(Power_Management() == 0 || STATUS_Motor_disabled) { motors.brake(10); return; }  // usb power
  
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

int read_QRED_distance(int F_Pin_number){  // QRE_Digital output
  pinMode( F_Pin_number, OUTPUT );
  digitalWrite( F_Pin_number, HIGH );
  delayMicroseconds(10);
  pinMode( F_Pin_number, INPUT );

  long time = micros();

  while (digitalRead(F_Pin_number) == HIGH && micros() - time < 3000); // value is between 0~3000(3cm)
  int diff = micros() - time; 
  return diff; 
}
