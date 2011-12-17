const unsigned int BUTTON_PIN = 7;
const unsigned int LED_PIN    = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

int led_state = LOW; // <label id="code.binary_die.led_state"/>

void loop() {
  const int CURRENT_BUTTON_STATE = digitalRead(BUTTON_PIN);

  if (CURRENT_BUTTON_STATE == HIGH) {
    led_state = (led_state == LOW) ? HIGH : LOW;
    digitalWrite(LED_PIN, led_state);
  }
}

