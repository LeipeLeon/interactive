#define SENSOR 1
#define LED 9

int val = 0 ;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(SENSOR);
  Serial.println(val);
  analogWrite(LED, val/4);
  delay(10);
}
