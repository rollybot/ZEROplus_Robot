#define ACRO HIGH
#define LTR  LOW

const byte speaker_PIN = 9;
const byte select_PIN  = 2;
const byte TRIG_PIN = 12;     
const byte ECHO_PIN = 11;  
const byte LED_PIN  = 13;

unsigned long duration;
unsigned long distance;
const int threshold = 5; //cm

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(ECHO_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = microsecondsToCentimeters(duration);
  Serial.print(distance);
  Serial.println(" cm");

  if(digitalRead(select_PIN) == ACRO) indicate_LED();
  else indicate_buzzer();

  delay(100);
}

void indicate_LED() {
  if (distance < threshold) digitalWrite(LED_PIN, HIGH);
  else digitalWrite(LED_PIN, LOW);
}

void indicate_buzzer() {
  if (distance < threshold) tone(speaker_PIN,1);
  else noTone(speaker_PIN);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

