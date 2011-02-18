/*
  http://www.tigoe.net/pcomp/code/category/arduinowiring/514
*/

// 2-dimensional array of column pin numbers: (anode) +
const int col[8] = {2,3,4,5,14,15,16,17};

// 2-dimensional array of row pin numbers: (cathode) -
const int row[8] = {6,7,8,9,10,11,12,13};

// 2-dimensional array of pixels:
int pixels[8][8];           

// cursor position:
int x = 5;
int y = 5;

// SPI communication
// Pin connected to ST_CP of 74HC595 (12)
int latchPin = 2;
// Pin connected to SH_CP of 74HC595 (11)
int clockPin = 3;
// Pin connected to DS of 74HC595 (14)
int dataPin  = 4;
int ledState[8] = {1, 2, 4, 8, 16, 32, 64, 128 };

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the anodes) low to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], LOW);
  }

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    digitalWrite(row[x], HIGH);
    digitalWrite(col[x], LOW);
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }
}

void loop() {
  testLoop();
//  // read input:
//  readSensors();
//  // draw the screen:
//  refreshScreen();
}

void readSensors() {
  // turn off the last position:
  pixels[x][y] = LOW;
  // read the sensors for X and Y values:
  x = 7 - map(analogRead(A4), 0, 1023, 0, 7);
  y =     map(analogRead(A5), 0, 1023, 0, 7);
  pixels[x][y] = HIGH;
}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        delay(30);
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}

void testLoop() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (cathode) low:
    digitalWrite(row[thisRow], LOW);
    // iterate over the cols (anodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {

      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisCol]);
      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
      delay(10);

    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], HIGH);
  }
}
