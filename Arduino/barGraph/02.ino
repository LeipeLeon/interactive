#define LED 13                // input pin LED
#define BUTTON 7              // input pushbutton 
int val = 0                   // state input pin pushbutton

void setup() {
  pinMode(LED,    OUTPUT);    // LED is an output
  pinMode(BUTTON, INPUT);     // BUTTON is an input
}

void loop() {
  val = digitalRead(BUTTON);  // read input
  
  // check if input is high
  if (val == HIGH) {
    digitalWrite(LED, HIGH);  // turn it on
  } else {
    digitalWrite(LED, LOW);   // turn it off
  }
}