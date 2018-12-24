////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// Buzzer control
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

void playsong_poweron(){
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    NewTone(SOUND_BUZZER_PIN, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noNewTone(SOUND_BUZZER_PIN); }
}

void playsong_No_sensor(int interval) {   // blink the LED every this interval
  unsigned long currentTime = millis();
  if(currentTime - index_Buzzer_startTime > interval) {
    index_Buzzer_startTime = currentTime;   
    NewTone(SOUND_BUZZER_PIN, melody[0], 10);
    delay(50);
    noNewTone(SOUND_BUZZER_PIN);
    NewTone(SOUND_BUZZER_PIN, melody[0], 10);
    delay(50);
    noNewTone(SOUND_BUZZER_PIN);
  }
  
}void playsong_interval(int interval) {   // blink the LED every this interval
  unsigned long currentTime = millis();
  if(currentTime - index_Buzzer_startTime > interval) {
    index_Buzzer_startTime = currentTime;   
    NewTone(SOUND_BUZZER_PIN, melody[0], 10);
    delay(10);
    noNewTone(SOUND_BUZZER_PIN);
  }
}


void playsong(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    NewTone(SOUND_BUZZER_PIN, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noNewTone(SOUND_BUZZER_PIN); }
}

void make_alarm(long Mtime) {
  pinMode(SOUND_BUZZER_PIN, OUTPUT);
  
  digitalWrite(SOUND_BUZZER_PIN,HIGH);   
  delay(Mtime);
  digitalWrite(SOUND_BUZZER_PIN, LOW);   
}
