#ifndef CONFIGURATION_H
#define CONFIGURATION_H

///////////////// BATT ////////////////////////////////////////////////////////
#define MAX_BATT_VOLT  5500     // 4*AA batt   3.5~5.5V(6.0 for alkaline)
#define LOW_BATT_VOLT  4800     // 4.8V
#define CUT_BATT_VOLT  4100     // 4.1v
#define NO_BATT        500 

///////////////// LED_Blink/////////////////////////////////////////////////////
#define NO_BLINK        0         // always on     
#define BLINK_LOW       1000      // 1 sec
#define BLINK_FAST      200       // 0.2 sec

///////////////// Ultrasonics //////////////////////////////////////////////////
#define TRESHOLD        10         // cm     

///////////////// Motor Select and varialble ///////////////////////////////////
// 장애물감지 주행시, 양쪽모터의 속도가 상이하면, 아래  MOTOR_BALANCE값을 조정한다. (왼쪽으로 치우치면 +값, 오른쪽으로 치우치면 -값입력)

#define MOTOR_BALANCE   0         // + value to the left side, - value to the right side (0~20)

#define LTRspeed        100       // N20
#define KP              0.4       // start with 0.1   before 0.3   (1.0
#define KD              1.0       // start with 5     before 1.5 (0.45
#define GAP_time        200       // control the gap between lines

#define MAXspeed        200       // 0~255
#define RUNspeed        100       // normal speed
#define MINspeed        80        // go to charger speed, calibrate speed

///////////////// QTR (Line trace)//////////////////////////////////////////////
#define QTR_RAW_thre    100       // analogread values of black line detect threshold "analogRead(QTR3_PIN)" (0-1024)
#define QTR_CAL_thre    500       // calibrated values of black line detect with "qtra.readCalibrated(sensorValues)" (0-1024)

///////////////// LineTracer Right-turn SENSOR /////////////////////////////////
// 만약 우회전센서을 장착하였으면, 아래 define문을 활성화시킵니다. (make enable if R-turn sensor is installed)
// Vislay정품센서 사용필요 (저가 중국산은 에러발생!!)    
                              
//#define R_TURN_SENSOR_ENABLED   

///////////////// Black line check for Autonomous Mode /////////////////////////
// 장애물감지 주행시, Black 라인을 감지하여 회피하고 싶다면 아래 define문을 활성화시킨다.

//#define BLACKline_ENABLED



#endif //__CONFIGURATION_H
