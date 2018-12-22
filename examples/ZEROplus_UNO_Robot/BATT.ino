////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
///////////////////////////////////            BATT            ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// The voltage of 4 x AA cells can vary between 3.5 – 5.5 V (and even to 6 V if alkalines are used).
// analogRead(adc)*5000*3/2/1023 = value of batt mV

int Power_Management() {
  Batt_LED_status(LED_interval);            // battary check LED status
  read_batt_volt = Battery_Volts();
  
  if(read_batt_volt < NO_BATT) {            // stop motor for programming with USB power
    LED_interval = BLINK_FAST;         
    return 0;
  }
  
  if(STATUS_Motor_disabled) {playsong_interval(2000); return 1;}
  
  if(read_batt_volt < CUT_BATT_VOLT) {      // stop motor system for safety
     COUNT_batt_volt++;
     if(COUNT_batt_volt >100) { 
       LED_interval = BLINK_FAST;  COUNT_batt_volt = 1; 
       STATUS_Motor_disabled = true;
     }
     return 1;
  }
  if(read_batt_volt < LOW_BATT_VOLT) {      // battery warning
     COUNT_batt_volt++;
     if(COUNT_batt_volt >10) { 
       LED_interval = BLINK_LOW;  COUNT_batt_volt = 1;
     }
     return 2;
  }
  LED_interval = NO_BLINK;
  return 3;
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

