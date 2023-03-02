
void DEBUG_Serial_monitor(int interval) {   // displaying debug in serial monitor
  unsigned long currentTime = millis();
  if(currentTime - index_Serial_startTime > interval) {
    index_Serial_startTime = currentTime;   
//    Serial.print(" battery volt : "); Serial.println(analogRead(BATT_READ_PIN));
    Serial.print(" battery volt : "); Serial.print(Battery_Volts()); Serial.println(" mv");
  }
}
