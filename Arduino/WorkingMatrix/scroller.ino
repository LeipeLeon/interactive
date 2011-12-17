#include <avr/pgmspace.h>

int sensorShiftDuration = 50;

void scroller() {
  byte letters[7] = { 1, 72, 101, 108, 108, 111, 2 };
  for (int thisLetter = 0; thisLetter < 7; thisLetter++) {
    Serial.println("");
    Serial.print("Letter: ");
    Serial.print(thisLetter);
    scrollLetter(my_chars[letters[thisLetter]]);
  }
}

void scroller2() {
  String display_txt = "Hello World! ";
  for (int thisLetter = 0; thisLetter < display_txt.length(); thisLetter++) {
    Serial.println("");
    Serial.print("Letter: ");
    Serial.print(display_txt[thisLetter]);
    scrollLetter(my_chars[display_txt[thisLetter]]);
  }
}

void scrollLetter(byte* letter) {
  for (int shift = 7; shift >= 0; shift--) {
    shiftPixels(letter, shift);
    for (int shiftDuration = 0; shiftDuration < sensorShiftDuration; shiftDuration++) {
      readSensors();
      refreshScreen();
    }
  }
}

void shiftPixels(byte* letter, int offset) {
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    pixels[thisRow] <<= 1;
    if (letter[thisRow] & (1 << offset)) {
      pixels[thisRow]++;
    } else {
      delay(1);
    }
  }
}

void printPixelBuffer() {
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    Serial.println(pixels[thisRow], BIN);
  }
  Serial.println("- - - - - - - - ");
}

void readSensors() {
  sensorShiftDuration = map(analogRead(A4), 0, 1023, 5, 100);
}
