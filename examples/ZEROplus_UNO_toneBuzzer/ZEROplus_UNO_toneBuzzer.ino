#include "pitches.h"

int melody[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };  // note durations: 4 = quarter note, 8 = eighth note, etc.:

const byte speakerPin = 9;
const byte LED_PIN = 13;

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(speakerPin);
  }
  delay(1000);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  tone(speakerPin, 1);
  delay(10);
  
  digitalWrite(LED_PIN,  LOW);
  noTone(speakerPin);
  delay(1000);
}

