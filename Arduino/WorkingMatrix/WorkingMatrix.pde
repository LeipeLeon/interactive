/* http://www.tigoe.net/pcomp/code/category/arduinowiring/514 */

// 2-dimensional array of column pin numbers: (anode) +
const int col[8] = {2,3,4,5,14,15,16,17};

// 2-dimensional array of row pin numbers: (cathode) -
const int row[8] = {6,7,8,9,10,11,12,13};

// 2-dimensional array of pixels:
int pixels[8][32];

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

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    digitalWrite(row[x], HIGH);
    for (int y = 0; y < 32; y++) {
      digitalWrite(col[y], LOW);
      pixels[x][y] = LOW;
    }
  }
  testLoop();
}

void loop() {
  // read input:
  readSensors();
  // draw the screen:
  refreshScreen();
}

void readSensors() {
  // turn off the last position:
  pixels[x][y] = LOW;
  // read the sensors for X and Y values:
  x = 7 - map(analogRead(A4), 0, 1023, 0, 7);
  y =     map(analogRead(A5), 0, 1023, 0, 31);
  pixels[x][y] = HIGH;
}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {

    digitalWrite(latchPin, LOW);      // ready up the 74HC595's to receive data

    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(0, thisRow)); // send data for matrix 1 red
    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(1, thisRow)); // send data for matrix 2 red
    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(2, thisRow)); // send data for matrix 1 green
    shiftOut(dataPin, clockPin, MSBFIRST, columnsForMatrix(3, thisRow)); // send data for matrix 2 green

    digitalWrite(row[thisRow], LOW);  // take the row pin (cathodes) low:
    digitalWrite(latchPin, HIGH);     // take the latch pin high so the LEDs will light up:
    delay(1);
    digitalWrite(row[thisRow], HIGH); // take the row pin HIGH to turn off the whole row:
    delay(1);
  }
}

// Calculate the leds who have to be on for this row
// TODO: refactor it for speed
int columnsForMatrix(int matrix, int row) {
  int leds = 0;
  for (int c = 0; c < 8; c++) {
    if (HIGH == pixels[row][c + (matrix * 8)]) {
      leds += ledState[c];
    }
  }
  return leds;
}

void testLoop() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (cathode) low:
    digitalWrite(row[thisRow], LOW);
    // iterate over the cols (anodes):
    for (int thisCol = 0; thisCol < 32; thisCol++) {

      digitalWrite(latchPin, LOW);
      // shift out the bits:
      if (thisCol < 8) {
        shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisCol]);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      } else if (thisCol < 16) {
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisCol - 8]);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      } else if (thisCol < 24) {
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisCol - 16]);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      } else {
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisCol - 24]);
      }
      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
      delay(10);

    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], HIGH);
  }
}
