#include <avr/pgmspace.h>

byte _H[8] = {
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B01100110,
  B01100110,
  B00000000
};

byte _E[8] = {
  B00000000,
  B01111110,
  B01100000,
  B01111000,
  B01100000,
  B01100000,
  B01111110,
  B00000000
};

byte _L[8] = {
  B00000000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01111110,
  B00000000
};

byte _O[8] = {
  B00000000,
  B01111110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B00000000
};

byte _SMILE[8] = {
  B00000000,
  B01100110,
  B01100110,
  B00000000,
  B01000010,
  B00111100,
  B00000000,
  B00000000
};

void hello() {
  byte* letters[7] = { _SMILE, _H, _E, _L, _L, _O, _SMILE };

  for (int thisLetter = 0; thisLetter < 6; thisLetter++) {
    writeLetter(letters[thisLetter], letters[thisLetter+1]);
  }

}

void writeLetter(byte* first, byte* second) {
  for (int duration = 0; duration < 500; duration++) {
    for (int thisRow = 0; thisRow < 8; thisRow++) {
      digitalWrite(latchPin, LOW);      // ready up the 74HC595's to receive data
      shiftOut(dataPin, clockPin, MSBFIRST, ledState[thisRow]); // send data for row
      shiftOut(dataPin, clockPin, MSBFIRST, first[thisRow]); // send data for matrix 1 red
      shiftOut(dataPin, clockPin, MSBFIRST, second[thisRow]); // send data for matrix 2 red
  //    shiftOut(dataPin, clockPin, MSBFIRST, ~ first[thisRow]); // send data for matrix 1 green
  //    shiftOut(dataPin, clockPin, MSBFIRST, ~ second[thisRow]); // send data for matrix 2 green

      digitalWrite(latchPin, HIGH);     // take the latch pin high so the LEDs will light up:
    }
  }
}
