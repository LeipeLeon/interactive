/* http://www.tigoe.net/pcomp/code/category/arduinowiring/514 */

// 2-dimensional array of column pin numbers: (anode) +
const int col[8] = {2,3,4,5,14,15,16,17};
// on my matrix that's pin 5, 6, 7, 8, 9, 10, 11, 12 for red
//                        13, 14, 15, 16,17, 18, 19, 20 for green

// 2-dimensional array of row pin numbers: (cathode) -
const int row[8] = {6,7,8,9,10,11,12,13};
// on my matrix that's pin 1, 2, 3, 4, 21, 22, 23, 24

// 2-dimensional array of pixels:
long pixels[8] = {0,0,0,0,0,0,0,0};

// cursor position:
int x = 5;
int y = 5;

// SPI communication
// Pin connected to ST_CP of 74HC595 (12)
int latchPin = 8;
// Pin connected to SH_CP of 74HC595 (11)
int clockPin = 7;
// Pin connected to DS of 74HC595 (14)
int dataPin  = 10;
int ledState[8] = {1, 2, 4, 8, 16, 32, 64, 128 };

void setup() {
  // initialize the serial port:
  // Serial.begin(9600);
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

  // test the matrix
  //  testLoop();
  testloopHorizontal();
  testloopVertical();
}

void loop() {
//   scroller();
  scroller2();
//  // read input:
//  readSensors();
//  // draw the screen:
//  refreshScreen();
}

// void readSensors() {
//   // turn off the last position:
//   pixels[x][y] = LOW;
//   // read the sensors for X and Y values:
//   x = 7 - map(analogRead(A4), 0, 1023, 0, 7);
//   y =     map(analogRead(A5), 0, 1023, 0, 31);
//   pixels[x][y] = HIGH;
// }

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {

    digitalWrite(latchPin, LOW);      // ready up the 74HC595's to receive data

    shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisRow]); // send data for row
    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(1, thisRow)); // send data for matrix 2 red
    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(0, thisRow)); // send data for matrix 1 red
//    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(2, thisRow)); // send data for matrix 1 green
//    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(3, thisRow)); // send data for matrix 2 green
    digitalWrite(latchPin, HIGH);     // take the latch pin high so the LEDs will light up:
  }
}

// Calculate the leds who have to be on for this row
// TODO: refactor it for speed
byte columnsForMatrix(int matrix, int row) {
  return pixels[row] >> (matrix * 8);
}
