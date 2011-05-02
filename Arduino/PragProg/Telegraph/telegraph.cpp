// START:init
#include <ctype.h>
#include <WProgram.h>
#include "telegraph.h"

char* LETTERS[] = {
  ".-",   "-...", "-.-.", "-..",  ".",    // A-E
  "..-.", "--.",  "....", "..",   ".---", // F-J
  "-.-",  ".-..", "--",   "-.",   "---",  // K-O
  ".--.", "--.-", ".-.",  "...",  "-",    // P-T
  "..-",  "...-", ".--",  "-..-", "-.--", // U-Y
  "--.."                                  // Z
};

char* DIGITS[] = {
  "-----", ".----", "..---", "...--", // 0-3
  "....-", ".....", "-....", "--...", // 4-7
  "---..", "----."                    // 8-9
};
// END:init

// START:constructor
Telegraph::Telegraph(const int output_pin, const int dit_length) {
  _output_pin = output_pin;
  _dit_length = dit_length;
  _dah_length = dit_length * 3;
  pinMode(_output_pin, OUTPUT);
}
// END:constructor
  
// START:send_message
void Telegraph::send_message(const char* message) {
  for (int i = 0; i < strlen(message); i++) {
    const char current_char = toupper(message[i]); // <label id="code.welcome.toupper"/>
    if (isalpha(current_char)) {
      output_code(LETTERS[current_char - 'A']);
      delay(_dah_length);
    } else if (isdigit(current_char)) {
      output_code(DIGITS[current_char - '0']);
      delay(_dah_length);
    } else if (current_char == ' ') { // <label id="code.welcome.blank"/>
      Serial.print(" ");
      delay(_dit_length * 7);
    }
  }
  Serial.println();
}
// END:send_message

// START:output_helper
void Telegraph::output_code(const char* code) {
  for (int i = 0; i < strlen(code); i++) {
    if (code[i] == '.')
      dit();
    else
      dah();
  }
}

void Telegraph::dit() {
  Serial.print(".");
  output_symbol(_dit_length);  
}

void Telegraph::dah() {
  Serial.print("-");
  output_symbol(_dah_length);
}

void Telegraph::output_symbol(const int length) {
  digitalWrite(_output_pin, HIGH);
  delay(length);
  digitalWrite(_output_pin, LOW);
}
// END:output_helper

/*
void Telegraph::output_symbol(const int length) {
  const int tone = 1915; // C
  for (long i = 0; i < length * 1000L; i += tone * 2) {
    digitalWrite(_output_pin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(_output_pin, LOW);
    delayMicroseconds(tone);
  }
}
*/
