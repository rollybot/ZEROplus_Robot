////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
/////LCD display & LED blinking ( ssd1306 i2c OLED )
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

void Show_LCD_display() {
  display.clearDisplay();
  display.drawRect( 0, 0,23,14,WHITE); display.fillRect(23, 4, 2, 6,WHITE);
  COUNT_batt_reading_OLED ++;
  if(COUNT_batt_reading_OLED > 5) {show_batt_volt = read_batt_volt; COUNT_batt_reading_OLED = 0;}
  if(show_batt_volt <= NO_BATT)   { display.setCursor(6 ,0); display.println("/"); }   
  if(show_batt_volt <= LOW_BATT_VOLT)  { Blink_batt_icon(1000); }               // Level blinking
  else {
    if(show_batt_volt > LOW_BATT_VOLT)     display.fillRect( 2, 2, 5,10,WHITE); // Level 1(>3.2)
    if(show_batt_volt > LOW_BATT_VOLT+0.4) display.fillRect( 9, 2, 5,10,WHITE); // Level 2(>3.6)
    if(show_batt_volt > MAX_BATT_VOLT-0.4) display.fillRect(16, 2, 5,10,WHITE); // Level 3(>3.8)
  }
  display.setCursor(68, 0); 
  if(show_batt_volt <= NO_BATT) display.println("-USB-");
  else {display.print(show_batt_volt/1000); display.println("v");}  // mv --> v
  display.setCursor(0 ,17); display.println("MODE:"); 
  display.setCursor(60,17); display.print(digitalRead(MODE_SELECT_PIN)? "AUTO" : "LTR");
  display.setCursor(0 ,34); display.print("SONAR:"); display.print(STATUS_Sonar_disabled ? "NO" : "YES");
  display.setCursor(0 ,51); display.println(" "); 
  display.display();
  delay(1);
}

void Blink_batt_icon(int interval) {   // blink the LED every this interval
  unsigned long currentTime = millis();
  if(currentTime - index_batt_LCD_startTime > interval) {
    COUNT_batt_low_blink_delay ++;
    display.clearDisplay();
    if (COUNT_batt_low_blink_delay > 3) {index_batt_LCD_startTime = currentTime; COUNT_batt_low_blink_delay = 0;}  
  }
}
