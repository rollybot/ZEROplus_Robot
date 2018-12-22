#define MAX_BATT_VOLT  5500     // 4*AA batt   3.5~5.5V(6.0 for alkaline)
#define LOW_BATT_VOLT  4800     // 5000
#define CUT_BATT_VOLT  4100     // 4500
#define NO_BATT        500 

const float resistorFactor = 5000*3/2/1023; // 7.3314
int COUNT_batt_volt = 1;             // for averging batt shutdown volt   
int temp_batt_volt =  0;

int Power_Management() {
  temp_batt_volt = Battery_Volts();
  if(temp_batt_volt < NO_BATT) {            // stop motor for programming with USB power     
    return 0;
  }
  
  if(temp_batt_volt < CUT_BATT_VOLT) {      // stop motor system for safety
     COUNT_batt_volt++;
     if(COUNT_batt_volt >100) { 
       COUNT_batt_volt = 1; 
       STATUS_Motor_disabled = true;
     }
     return 1;
  }
}

float Battery_Volts() {
  volatile int val = readAverage();
  volatile float volts_fix = val*7.3314;  // 4*AA batt mV 
  return volts_fix;
}

unsigned int readAverage() {
  int voltageValue = 0;
  for (int i = 0; i < 10; i++)
  { 
    voltageValue += analogRead(BATT_READ_PIN);
    delay(2);
  }
  return (voltageValue / 10);  // mV
}

