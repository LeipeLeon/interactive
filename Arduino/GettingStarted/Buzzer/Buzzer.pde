#define BUZZER 9 // output for buzzer
#define BUTTON 8 // on/off
#define FREQ   1 // frequency input 

int freq = 244;  // frequency
                 // 1 / 2048Hz = 488uS, or 244uS high and 244uS low to create 50% duty cycle

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  freq = map(analogRead(FREQ), 0, 1023, 244, 488);
//  Serial.println(freq);    

//  if (digitalRead(BUTTON)) {
    for (long i = 0; i < (610 - freq); i++ ) {
      digitalWrite(BUZZER, HIGH);
      delayMicroseconds(freq);
      digitalWrite(BUZZER, LOW);
      delayMicroseconds(freq);
    }
//  }
//  delay(10);
}
