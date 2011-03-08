
void testLoop() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 3; thisRow++) {
    // take the row pin (cathode) low:
    digitalWrite(row[thisRow], LOW);
    // iterate over the cols (anodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
  
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
      delay(100);
  
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], HIGH);
  }
}

void testloopHorizontal() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
      refreshScreen();
      pixels[x][y] = LOW;
    }
  }
}

void testloopVertical() {
  for (int y = 0; y < 32; y++) {
    for (int x = 0; x < 8; x++) {
      pixels[x][y] = HIGH;
      refreshScreen();
      pixels[x][y] = LOW;
    }
  }
}

