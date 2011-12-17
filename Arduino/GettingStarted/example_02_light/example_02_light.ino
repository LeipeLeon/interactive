#define LED    11             // input pin LED
#define BUTTON 0              // input pushbutton 
int val = 0 ;                 // state input pin pushbutton

void setup() {
  pinMode(LED,    OUTPUT);    // LED is an output
  pinMode(BUTTON, INPUT);     // BUTTON is an input
  Serial.begin(9600);
}

void loop() {
  val = map(analogRead(BUTTON), 280, 612, 0, 255);  // read input
  // check if input is high
  if (val > 128) {
    digitalWrite(LED, HIGH);  // turn it on
  } else {
    digitalWrite(LED, LOW);   // turn it off
  }
  Serial.println(val);
  delay(10);
}

