#ifndef PINS_H
#define PINS_H

///////////////// MAIN ///////////////////////////////////////////
#define BATT_READ_PIN     A0     // analog 0 for batt check, max Vin : 15V(3cell lipo), R2/(R1+R2) 
#define MODE_SELECT_PIN   2     // mode select pin, Following MODE/Normal MODE  (interrupt pin)
#define SOUND_BUZZER_PIN  9
#define POWER_LED_PIN     13     // body vibration (PWM) can use analogWrite()

#endif // PINS_H
