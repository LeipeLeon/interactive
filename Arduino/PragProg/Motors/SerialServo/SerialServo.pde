#include <Servo.h> 
 
const unsigned int MOTOR_PIN = 9;
const unsigned int MOTOR_DELAY = 15;
const unsigned int SERIAL_DELAY = 5;
const unsigned int BAUD_RATE = 9600;

Servo servo; // <label id="code.motors.servo"/>
 
void setup() { 
  Serial.begin(BAUD_RATE);
  servo.attach(MOTOR_PIN); // <label id="code.motors.servo_attach"/>
  delay(MOTOR_DELAY);
  servo.write(1);
  delay(MOTOR_DELAY);
} 
 
void loop() {
  const int MAX_ANGLE = 3;
  
  char degrees[MAX_ANGLE + 1]; // <label id="code.motors.degrees"/>
  
  if (Serial.available()) {
    int i = 0;
    while (Serial.available() && i < MAX_ANGLE) {
      const char c = Serial.read();
      if (c != -1 && c != '\n')
        degrees[i++] = c;
      delay(SERIAL_DELAY);
    }
    degrees[i] = 0;
    Serial.print(degrees);
    Serial.println(" degrees.");
    servo.write(atoi(degrees)); // <label id="code.motors.servo_write"/>
    delay(MOTOR_DELAY);
  }
} 
