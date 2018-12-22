#ifndef CONFIGURATION_H
#define CONFIGURATION_H

///////////////// BATT ////////////////////////////////////////////////////////
#define MAX_BATT_VOLT  5500     // 4*AA batt   3.5~5.5V(6.0 for alkaline)
#define LOW_BATT_VOLT  4800     // 5000
#define CUT_BATT_VOLT  4100     // 4500
#define NO_BATT        500 

///////////////// LED_Blink/////////////////////////////////////////////////////
#define NO_BLINK       0        // always on     
#define BLINK_LOW      1000     // 1 sec
#define BLINK_FAST     200      // 0.2 sec  

///////////////// Motor Select and varialble ///////////////////////////////////
#define MOTOR_BALANCE   0        // + value to the left side, - value to the right side (0~20)

#define MAXspeed        200      // 0~255
#define RUNspeed        100      // normal speed
#define MINspeed        80       // go to charger speed, calibrate speed

#endif //__CONFIGURATION_H

