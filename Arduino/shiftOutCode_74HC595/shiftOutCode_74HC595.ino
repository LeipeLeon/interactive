//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int BEAT = 13;

byte ledCharSet[10] = {
//	// 00-0F: Hex digits
//	B01111110, B00110000, B01101101, B01111001,	// 0123
//	B00110011, B01011011, B01011111, B01110000,	// 4567
//	B01111111, B01111011, B01110111, B00011111,	// 89AB
//	B01001110, B00111101, B01001111, B01000111,	// CDEF
//
//	// 10-1F: Figure-8 drawing (8-character cycle)
//	B01000000, B00100000, B00000001, B00000100,	// 1-segment
//	B00001000, B00010000, B00000001, B00000010,
//
//	B01100000, B00100001, B00000101, B00001100,	// 2-segment
//	B00011000, B00010001, B00000011, B01000010,
//
//	// 20-2F: Punctuation (barely recognizable!)
//	B00000000, B10100000, B00100010, B00111111,	//  !"#
//	B01011010, B01001001, B00000111, B00000010,	// $%&'
//	B01001110, B01111000, B01100011, B00110001,	// ()*+
//	B00010000, B00000001, B10000000, B00100101,	// ,-./
//
	// 30-3F: Decimal digits (alternate) and more punctuation
	B01111110, B00110000, B01101101, B01111001,	// 0123
	B00110011, B01011011, B00011111, B01110010,	// 4567
	B01111111, B01110011
//, B01001000, B01010000,	// 89:;
//	B00001101, B00001001, B00011001, B11100000,	// <=>?
//
//	// 40-5F: Capital letters and punctuation
//	B01101110, B01110111, B00011111, B01001110,	// @ABC
//	B01111100, B01001111, B01000111, B01011110,	// DEFG
//	B00110111, B00000110, B00111100, B01010111,	// HIJK
//	B00001110, B01110110, B00010101, B01111110,	// LMNO
//
//	B01100111, B01110011, B01000110, B01011011,	// PQRS
//	B01110000, B00111110, B00111110, B00101011,	// TUVW
//	B01110101, B00111011, B01101101, B01001110,	// XYZ[
//	B00010011, B01111000, B01100010, B00001000,	// \]^_
//
//	// 60-7F: Lowercase letters and punctuation
//	B01100000, B01111101, B00011111, B00001101,	// `abc
//	B00111101, B01101111, B01000111, B01111011,	// defg
//	B00010111, B00010000, B00011000, B00101111,	// hijk
//	B00001100, B01010101, B01101010, B00011101,	// lmno
//
//	B01100111, B01110011, B00000101, B00010011,	// pqrs
//	B00001111, B00011100, B00100011, B01011101,	// tuvw
//	B01101100, B00111011, B00100101, B01000011,	// xyz{
//	B00110110, B01100001, B01000000, B11111111	// |}~
};


void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(BEAT, OUTPUT);
  Serial.begin(9600);    
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 10; numberToDisplay++) {
//    digitalWrite(BEAT, HIGH);
     // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    Serial.print(numberToDisplay);
    Serial.print("\n");
    Serial.print(ledCharSet[numberToDisplay], BIN);
    Serial.print("\n");
    shiftOut(dataPin, clockPin, LSBFIRST, ledCharSet[numberToDisplay]);  
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
//    digitalWrite(BEAT, LOW);
    delay(500);
  }
//  delay(1000);
}
