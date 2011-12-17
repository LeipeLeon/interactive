/*
  Row-Column Scanning an 8x8 LED matrix with X-Y input
 
 This example controls an 8x8 LED matrix using two analog inputs
 
 created 27 May 2009
 modified 4 Sep 2010
 by Tom Igoe
 
 This example works for the Lumex  LDM-24488NI Matrix. See 
 http://sigma.octopart.com/140413/datasheet/Lumex-LDM-24488NI.pdf
 for the pin connections
 
 For other LED cathode column matrixes, you should only need to change 
 the pin numbers in the row[] and column[] arrays
 
 rows are the anodes
 cols are the cathodes
 ---------
 
 Pin numbers:
 Matrix:
 * Digital pins 2 through 13,
 * analog pins 2 through 5 used as digital 16 through 19
 Potentiometers:
 * center pins are attached to analog pins 0 and 1, respectively
 * side pins attached to +5V and ground, respectively.
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/RowColumnScanning
 
 see also http://www.tigoe.net/pcomp/code/category/arduinowiring/514 for more
 */


// 2-dimensional array of row pin numbers: (anode) +
const int col[8] = {2,3,4,5,14,15,16,17};

// 2-dimensional array of column pin numbers: (cathode) -
const int row[8] = {6,7,8,9,10,11,12,13};

// 2-dimensional array of pixels:
int pixels[8][8];           

// cursor position:
int x = 5;
int y = 5;

void setup() {
  Serial.begin(9600);
  // initialize the I/O pins as outputs:

  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin], HIGH);    
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }
}

void loop() {
  // read input:
  readSensors();

  // draw the screen:
  refreshScreen();
  delay(10);
}

void readSensors() {
  // turn off the last position:
  pixels[x][y] = LOW;
  // read the sensors for X and Y values:
  x = 7 - map(analogRead(A4), 0, 1023, 0, 7);
  y =     map(analogRead(A5), 0, 1023, 0, 7);
  // set the new pixel position low so that the LED will turn on
  // in the next screen refresh:
  pixels[x][y] = HIGH;
}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    digitalWrite(row[thisRow], HIGH);
    // take the row pin (anode) high:
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      digitalWrite(col[thisCol], thisPixel);
      if (thisPixel == HIGH) {
        digitalWrite(row[thisRow], LOW);
      }
    }
    // take the row pin low to turn off the whole row:
//    digitalWrite(row[thisRow], HIGH);
  }
}
