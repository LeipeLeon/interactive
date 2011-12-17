
void testLoop() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // iterate over the cols (anodes):
    for (int thisCol = 0; thisCol < 16; thisCol++) {
      digitalWrite(latchPin, LOW);
      // send data for row
      shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisRow]);
      // shift out the bits:
      if (thisCol < 8) {
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
        shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisCol]);
//        shiftOut(dataPin, clockPin, MSBFIRST, 0);
//        shiftOut(dataPin, clockPin, MSBFIRST, 0);
      } else if (thisCol < 16) {
        shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisCol - 8]);
        shiftOut(dataPin, clockPin, MSBFIRST, 0);
//        shiftOut(dataPin, clockPin, MSBFIRST, 0);
//        shiftOut(dataPin, clockPin, MSBFIRST, 0);
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
  }
}

void testloopHorizontal() {
  for (int x = 0; x < 8; x++) {     // set initial state
    pixels[x] = 1;
    for (byte y = 0; y < 16; y++) {   // for 2 matrices (2 * 8)
      refreshScreen();
      pixels[x] <<= 1;
    }
    pixels[x] = 0;
  }
}

void testloopVertical() {
  int memo = 1;
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 8; x++) {
      pixels[x] = memo;
      refreshScreen();
      pixels[x] = 0;
    }
    memo <<= 1;
  }
}

