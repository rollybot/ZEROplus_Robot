////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    Serial.println("[ZEROplus]Debugging");
    Serial.print("*MODE : ");   Serial.print(Switch_line_follow_mode ? "LTR" : "AUTO");  Serial.print("     "); 
    Serial.print("*Batt : ");   Serial.print((float)read_batt_volt/1000);  Serial.print(" V"); Serial.print("     ");
    Serial.print("*SONAR : ");  Serial.print(STATUS_Sonar_disabled ? 0 : read_sonar_cm); Serial.println(" cm");
    Serial.print("*QTR5 : ");   Serial.println(read_QRED_distance(QTR5_PIN)); 
    Serial.println(" ");
  }
}
