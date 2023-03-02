void Show_LCD_display() {
  display.clearDisplay();
  display.fillRect(0, 0,128, 17, WHITE);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(17 , 1); display.println("ZEROplus"); 
  display.setTextColor(WHITE);
  display.setCursor(0 ,17); display.println(" "); 
  display.setCursor(0 ,34); display.println("MODE:");
  display.setCursor(60,34); display.print(digitalRead(MODE_SELECT_PIN)? "AUTO" : "LTR");
  display.setCursor(0 ,51); display.println("SONAR:"); 
  display.setCursor(70,51); display.print(STATUS_Sonar_disabled ? "NO" : "YES");
  display.display();
  delay(1);
}
