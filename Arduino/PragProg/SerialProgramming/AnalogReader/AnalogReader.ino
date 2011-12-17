const unsigned int BAUD_RATE = 9600;
const unsigned int SERIAL_DELAY = 5;
const unsigned int NUM_PINS = 6;

void setup() { 
  Serial.begin(BAUD_RATE);
} 
 
void loop() {
  const int MAX_PIN_NAME = 3;
  
  char pin_name[MAX_PIN_NAME + 1];
  
  if (Serial.available()) {
    int i = 0;
    while (Serial.available() && i < MAX_PIN_NAME) {
      const char c = Serial.read();
      if (c != -1 && c != '\n')
        pin_name[i++] = c;
      delay(SERIAL_DELAY);
    }
    pin_name[i] = 0;
    if (strlen(pin_name) > 1 &&
        (pin_name[0] == 'a' || pin_name[0] == 'A'))
    {
      const int pin = atoi(&pin_name[1]);
      if (pin < NUM_PINS) {
        Serial.print(pin_name);
        Serial.print(": ");
        Serial.println(analogRead(pin));
      } else {
        Serial.print("Unknown pin: ");
        Serial.println(pin);
      }
    } else {
      Serial.print("Unknown pin name: ");
      Serial.println(pin_name);
    }
  }
}

