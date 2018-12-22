//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LED, LCD Blink 

void Batt_LED_status(int interval) {   // blink the LED every this interval
  if(interval == 0) {digitalWrite(POWER_LED_PIN, HIGH); return;}
  unsigned long currentTime = millis();
  if(currentTime - index_Power_LED_startTime > interval) {
    index_Power_LED_startTime = currentTime;   
    if (state_Power_LED == LOW)  state_Power_LED = HIGH;
    else state_Power_LED = LOW;
    digitalWrite(POWER_LED_PIN, state_Power_LED);
  }
}

void DEBUG_Serial_monitor(int interval) {   // displaying debug in serial monitor
  unsigned long currentTime = millis();
  if(currentTime - index_Serial_startTime > interval) {
    index_Serial_startTime = currentTime;   
    Serial.print(" *battery volt : "); Serial.print(temp_batt_volt < 500 ? 0000 : temp_batt_volt); Serial.print("  ");
    Serial.print(" *line sensor  : "); 
    Serial.print(sensorValues[0]); Serial.print("  ");
    Serial.print(sensorValues[1]); Serial.print("  ");
    Serial.print(sensorValues[2]); Serial.println("  ");
  }
}
