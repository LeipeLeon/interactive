#include <avr/pgmspace.h>

byte H[8] = {
  B00000000,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B01100110,
  B01100110,
  B00000000
};

byte E[8] = {
  B00000000,
  B01111110,
  B01100000,
  B01111000,
  B01100000,
  B01100000,
  B01111110,
  B00000000
};

byte L[8] = {
  B00000000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01111110,
  B00000000
};

byte O[8] = {
  B00000000,
  B01111110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B00000000
};

byte SMILE[8] = {
  B00000000,
  B01100110,
  B01100110,
  B00000000,
  B01000010,
  B00111100,
  B00000000,
  B00000000
};

void scroller() {
  byte* letters[7] = { SMILE, H, E, L, L, O, SMILE };
  for (int thisLetter = 0; thisLetter < 7; thisLetter++) {
    Serial.println("");
    Serial.print("Letter: ");
    Serial.print(thisLetter);
    scrollLetter(letters[thisLetter]);
  }
}

void scrollLetter(byte* letter) {
  for (int shift = 7; shift >= 0; shift--) {
    shiftPixels(letter, shift);
    for (int shiftDuration = 0; shiftDuration < 50; shiftDuration++) {
      refreshScreen();
    }
  }
}

void shiftPixels(byte* letter, int offset) {
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    pixels[thisRow] <<= 1;
    if (letter[thisRow] & (1 << offset)) {
      pixels[thisRow]++;
    }
  }
}

void printPixelBuffer() {
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    Serial.println(pixels[thisRow], BIN);
  }
  Serial.println("- - - - - - - - ");
}
