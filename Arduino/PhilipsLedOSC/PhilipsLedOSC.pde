/*
Philips Mood lightning
Derived from http://www.sparkfun.com/tutorials/152

Control the LED (with Processing/OSC) by a serial command.

To control LED R G or B send a (byte) message over the serial line in the format of 
  
  byte(val)
  byte(color)

ex:
  123R
  72G
  0B

Because of control caracters below ASCII 127 the value range is 128 - 255.
this will be mapped to 0 - 255


WIRING:

RED    9 ---/\/\/---|>|--+
GREEN 10 ---/\/\/---|>|--+
BLUE  11 ---/\/\/---|>|--+
                         |
GND      ----------------+

*/

#define RED     9  // PWM pin 9 
#define GREEN  10  // PWM pin 10
#define BLUE   11  // PWM pin 11
#define BEAT   13  // soldered on LED

// We create a buffer to memorize values from the serial input
char buff[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);      // set serial to 9600 baud rate
  pinMode(RED,   OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE,  OUTPUT);
}

void loop(){
  if (Serial.available() > 0) { //  Check if there is a new message

    // shift the buffer
    for (int i=0; i<10; i++) {
      buff[i]=buff[i+1];
    }

    // put last recieved byte into the buffer
    buff[10] = Serial.read();

    if (buff[10] == 'R') {
      analogWrite(RED,   calculateColor());
    }
    if (buff[10] == 'G') {
      analogWrite(GREEN, calculateColor());
    }
    if (buff[10] == 'B') {
      analogWrite(BLUE,  calculateColor());
    }
  }
}

// retrieve value from previous byte from buffer
// and map it back to a range from 128-155 to 0 - 255
int calculateColor() {
  return int((byte(buff[9]) - 128) * 2);
}

