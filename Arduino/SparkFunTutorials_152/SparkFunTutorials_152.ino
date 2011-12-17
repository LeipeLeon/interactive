// http://www.sparkfun.com/tutorials/152

// RED    ---|>|---/\/\/--+
// GREEN  ---|>|---/\/\/--+
// BLUE   ---|>|---/\/\/--+
//                        |
// GND    ----------------+

#define RED     9  // RED   pin of the LED to PWM pin 9 
#define GREEN  10  // GREEN pin of the LED to PWM pin 10
#define BLUE   11  // BLUE  pin of the LED to PWM pin 11
#define BEAT   13  // soldered on LED

int message   = 0;    //  This will hold one byte of the serial message
int redLEDPin = 6;    //  What pin is the red LED connected to?
int redLED    = 0;    //  The value/brightness of the LED, can be 0-255

int redValue   = 0;
int blueValue  = 0;
int greenValue = 0;
//String rgb = "";

char buff[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char tmp;

void setup() {  
  Serial.begin(9600);  //set serial to 9600 baud rate
  pinMode(RED,   OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE,  OUTPUT);
}

void loop(){
  if (Serial.available() > 0) { //  Check if there is a new message

    // shift the buffer
    for (int i=0; i<10; i++) {
      buff[i]=buff[i+1];
//      Serial.print(buff[i], BYTE);
//      Serial.print(":");
    }
   
    buff[10] = Serial.read();

//    Serial.print(buff[10], BYTE);
//    Serial.print(" - ");

    if (buff[10] == 'R') {
      analogWrite(RED,       calculateColor());
      Serial.print("   RED: ");
      Serial.print(calculateColor());
    }
    if (buff[10] == 'G') {
      analogWrite(GREEN,     calculateColor());
      Serial.print(" GREEN: ");
      Serial.print(calculateColor());
    }
    if (buff[10] == 'B') {
      analogWrite(BLUE,      calculateColor());
      Serial.print("  BLUE: ");
      Serial.print(calculateColor());
    }
//    Serial.println(calculateColor(), DEC);
//    if (buff[10] == 1) {
//      redLED = int(buff[8]);
//      analogWrite(redLEDPin, redLED);  //  Write an analog value between 0-255
//    }
  }   
}

int calculateColor() {
  return int((byte(buff[9]) - 128) * 2);
}


/* Led Pixel script - www.anthonymattox.com
 * recieves input from processing script  */


