const unsigned int LED_PIN = 13;
const unsigned int PAUSE = 500;

void setup() { // <label id="code.welcome.setup"/>
  pinMode(LED_PIN, OUTPUT);
}

void loop() { // <label id="code.welcome.loop"/>
  digitalWrite(LED_PIN, HIGH);
  delay(PAUSE);
  digitalWrite(LED_PIN, LOW);
  delay(PAUSE);
}
