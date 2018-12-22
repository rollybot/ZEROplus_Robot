#include "pitches.h"
#define ACRO HIGH
#define LTR  LOW

const byte speakerPin = 9;
const byte interrupt_PIN = 2;
const byte LED_PIN = 13;
volatile byte state = LOW;

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(interrupt_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt_PIN), change_song, CHANGE);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  if(digitalRead(interrupt_PIN) == ACRO) GameOfThrones();
  else  PiratesOfCaribbean();
  
}
void(* resetDevice) (void) = 0;
void change_song() {
  resetDevice();
}

