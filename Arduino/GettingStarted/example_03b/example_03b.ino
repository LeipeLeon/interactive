#define LED    13             // input pin LED
#define BUTTON 7              // input pushbutton 
int val   = 0;                // state input pin pushbutton
int old_val = 0;              // store previous val
int state = 0;                // 0 = LED OFF, 1 = LED ON

void setup() {
  pinMode(LED,    OUTPUT);    // LED is an output
  pinMode(BUTTON, INPUT);     // BUTTON is an input
}

void loop() {
  val = digitalRead(BUTTON);  // read input

  if ((val == HIGH) && (old_val == LOW)) {
    state = 1 - state;
    delay(10)
  }

  old_val = val;

  // check if input is high
  if (state == 1) {
    digitalWrite(LED, HIGH);  // turn it on
  } else {
    digitalWrite(LED, LOW);   // turn it off
  }
}
