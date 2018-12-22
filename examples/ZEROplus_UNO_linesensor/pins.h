#ifndef PINS_H
#define PINS_H

///////////////// MAIN ///////////////////////////////////////////
#define BATT_READ_PIN     A0     // analog 0 for batt check, max Vin : 15V(3cell lipo), R2/(R1+R2) 
#define SPEED_SELECT_PIN   2     // mode select pin, Following MODE/Normal MODE  (before remocon pin)
#define SOUND_BUZZER_PIN   9
#define POWER_LED_PIN     13     // body vibration (PWM) can use analogWrite()

///////////////// QTR SENSORS ( TCRT5000) ////////////////////////
#define QTR2_PIN          A1     // Center Left   IR
#define QTR3_PIN          A2     // Center IR
#define QTR4_PIN          A3     // Center Right  IR

/////////////////  Motor (L293D Driver) ////////////

#define ENAB_A_PIN        5     // Motor A
#define DIR_A1_PIN        4     // 
#define DIR_A2_PIN        7     // 
#define ENAB_B_PIN        6     // Motor B
#define DIR_B1_PIN        3     // 
#define DIR_B2_PIN        8     // 

#endif // PINS_H
