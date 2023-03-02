int Power_Management() {
  read_batt_volt = Battery_Volts();
  if(read_batt_volt < NO_BATT) {            // stop motor for programming with USB power     
    return 0;
  }
  
  if(read_batt_volt < CUT_BATT_VOLT) {      // stop motor system for safety
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
  volatile float volts_fix = val*7.3314;
  return volts_fix;
}

unsigned int readAverage() {
  int voltageValue = 0;
  for (int i = 0; i < 10; i++) { voltageValue += analogRead(BATT_READ_PIN);  delay(2); }
  return (voltageValue / 10);  // mV
}

boolean CHECK_USB_powered() {
  if(Battery_Volts() < NO_BATT) {return 1;}
  else return 0;
}
