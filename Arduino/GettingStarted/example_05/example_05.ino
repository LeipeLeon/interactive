#define LED 9
#define BUTTON 7

int val     = 0;
int old_val = 0;
int state   = 0;

int brightness = 128;
unsigned long startTime = 0 ;

void setup() {
  pinMode(LED,    OUTPUT);    // LED is an output
  pinMode(BUTTON, INPUT);     // BUTTON is an input
}

void loop () {
  val = digitalRead(BUTTON);
  if ((HIGH == val) && (LOW == old_val)) {
    state = 1 - state ;
    startTime = millis();
    delay(50);
  }   
  if ((HIGH == val) && (HIGH == old_val)) {
    if (1 == state && (millis() - startTime) > 500) {
      brightness++;
      delay(10);
      if (brightness > 255) {
        brightness = 0;
      }
    }
  }
  old_val = val ;
  if (1 == state) {
    analogWrite(LED, brightness);
  } else {
    analogWrite(LED, 0);
  }
}  
