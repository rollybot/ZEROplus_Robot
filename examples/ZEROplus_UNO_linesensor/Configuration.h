#ifndef CONFIGURATION_H
#define CONFIGURATION_H

///////////////// BATT ////////////////////////////////////////////////////////
#define MAX_BATT_VOLT  5500     // 4*AA batt   3.5~5.5V(6.0 for alkaline)
#define LOW_BATT_VOLT  4800     // 5000
#define CUT_BATT_VOLT  4100     // 4500
#define NO_BATT        500 

///////////////// LED_Blink/////////////////////////////////////////////////////
#define NO_BLINK        0         // always on     
#define BLINK_LOW       1000      // 1 sec
#define BLINK_FAST      200       // 0.2 sec

///////////////// Motor Select and varialble ///////////////////////////////////
#define MOTOR_BALANCE   0         // + value to the left side, - value to the right side (0~20)

#define LTRspeed        100       // N20
#define KP              0.3       // start with 0.1   before 0.3   (1.0
#define KD              1.2       // start with 5     before 1.5 (0.45
#define GAP_time        70        // control the gap between lines

#define MAXspeed        200       // 0~255
#define RUNspeed        100       // normal speed
#define MINspeed        80        // go to charger speed, calibrate speed

///////////////// QTR (Line trace)//////////////////////////////////////////////
#define QTR_RAW_thre   100      // analogread values of black line detect threshold "analogRead(QTR3_PIN)" (0-1024)
#define QTR_CAL_thre   500      // calibrated values of black line detect with "qtra.readCalibrated(sensorValues)" (0-1024)
#define QTR_GAP_time   (long) (-(1.56*RUNspeed)+480)  // time = a*speed + K  using 2 experiment (speed,time) = (70,370)(250,90)


#endif //__CONFIGURATION_H

