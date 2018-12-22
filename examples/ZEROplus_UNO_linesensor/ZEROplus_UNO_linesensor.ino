#include <ZEROplus_Robot.h>
#include "pins.h"
#include "Configuration.h"

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

///////////////// GLOBAL and ETC VARIABLES ////////////////////////////////////////////////////////
boolean STATUS_Calibration_setup = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
    
  Serial.begin(9600);  
  delay(500);

  Setup_Calibration();
}

void loop() {
  qtra.readCalibrated(sensorValues);
  Serial.print  ("sensorValues[0]: "); Serial.print  (sensorValues[0]); Serial.print("  ");
  Serial.print  ("sensorValues[1]: "); Serial.print  (sensorValues[1]); Serial.print("  ");
  Serial.print  ("sensorValues[2]: "); Serial.println(sensorValues[2]); Serial.print("  ");
  delay(500);
}

