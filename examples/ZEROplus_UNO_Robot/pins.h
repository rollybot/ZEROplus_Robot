#ifndef PINS_H
#define PINS_H

///////////////// MAIN ///////////////////////////////////////////
#define BATT_READ_PIN     A0     // analog 0 for batt check, max Vin : 15V(3cell lipo), R2/(R1+R2) 
#define MODE_SELECT_PIN   2     // mode select pin, Following MODE/Normal MODE  (interrupt pin)
#define SOUND_BUZZER_PIN  9
#define POWER_LED_PIN     13     // body vibration (PWM) can use analogWrite()

///////////////// QTR SENSORS (TCRT5000) ////////////////////////
#define QTR2_PIN          A1     // Center Left   IR
#define QTR3_PIN          A2     // Center IR
#define QTR4_PIN          A3     // Center Right  IR

///////////////// Ultrasonic SENSORS (HC-SR04) ////////////////////////
#define TRIG_PIN          12     
#define ECHO_PIN          11     

#endif // PINS_H
