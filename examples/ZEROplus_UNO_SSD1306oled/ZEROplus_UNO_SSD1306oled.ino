// [프로그램 설명] OLED액정(SSD1306) 작동시키기
//
// **LCD에 표시하기 위해서는 우선, OLED액정(SSD1306)을 ZEROplus 로봇에 설치하여야 함**
// 액정을 설치하고 다양한 info(정보)를 액정에 표시하여, 로봇의 상태를 알수 있다. 여기서는
// 이 코드에서는 초음파센서의 유무, 모드스위치 상태, 배터리 잔량등을 파악할 수있다


#include <Rollybot_Motors_L293D.h>   // motor control
#include <Adafruit_SSD1306.h>        // OLED display
#include <NewPing.h>                 // ultrasonic sensor control
#include "pins.h"                    // pin mapping

#define BATT_READ_PIN    A0     // analog 0 for batt check, max Vin : 15V(3cell lipo), R2/(R1+R2) 
#define MODE_SELECT_PIN  2 
#define MAX_BATT_VOLT    5500     // 4*AA batt   3.5~5.5V(6.0 for alkaline)
#define LOW_BATT_VOLT    4800     // 5000
#define CUT_BATT_VOLT    4100     // 4500
#define NO_BATT          500 

Rollybot_Motors_L293D motors(ENAB_A_PIN, DIR_A1_PIN, DIR_A2_PIN, ENAB_B_PIN, DIR_B1_PIN, DIR_B2_PIN);
boolean STATUS_Motor_disabled = false;

///////////////// SSD1306 I2C(OLED) VARIABLES ////////////////////////////////////////////////////
#define OLED_RESET -1
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

long index_batt_LCD_startTime = 0; 


///////////////// LEDs (Power,Lower) VARIABLES ////////////////////////////////////////////////////
long index_Serial_startTime = 0;

///////////////// Ultrasonic VARIABLES ////////////////////////////////////////////////////////////
#define TRIG_PIN          12     
#define ECHO_PIN          11 
NewPing sonar(TRIG_PIN, ECHO_PIN, 400);
int  read_sonar_cm = 10;
long ping_duration = 1000;

///////////////// Battery (Voltage divider) VARIABLES /////////////////////////////////////////////
const float referenceVolts = 5;
const float resistorFactor = 5000*3/2/1023; // 7.3314

int   COUNT_batt_reading_OLED = 10;
int   COUNT_batt_volt = 1;             // for averging batt shutdown volt   
float read_batt_volt  = 0;
float show_batt_volt  = 0;
int   COUNT_batt_low_blink_delay = 0;  // for blinking

///////////////// GLOBAL and ETC VARIABLES ////////////////////////////////////////////////////////
int  loopTime  = 1 ;                   // every 0.001sec for looping (basic loop time)
long COUNT_for_shutdown_start   = 0;

///////////////// GLOBAL Switch VARIABLES ////////////////////////////////////////////////////////
boolean STATUS_battery_low       = false;
boolean STATUS_Chargering        = false;  //  for CHARGING
boolean STATUS_Sonar_disabled    = false;

void setup() {
  pinMode(BATT_READ_PIN,   INPUT);            
  pinMode(MODE_SELECT_PIN, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();

  motors.setMotorBalance(0);      // + value to the left side, - value to the right side
  motors.brake(1000);
  
  if(sonar.ping_cm() == 0) STATUS_Sonar_disabled = true;
  
  Serial.begin(9600);  
  delay(300);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  DEBUG_Serial_monitor(500);  // check every 0.5sec
  Show_LCD_display();         // LCD display
  if(Power_Management() == 0 || STATUS_Motor_disabled) { motors.brake(10); return; }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
