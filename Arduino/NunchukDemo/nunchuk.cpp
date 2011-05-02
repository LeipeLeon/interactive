#include <WProgram.h>
#include <Wire.h>
#include "nunchuk.h"

#define NUNCHUK_DEVICE_ID 0x52

void Nunchuk::initialize() {
  Wire.begin();
  Wire.beginTransmission(NUNCHUK_DEVICE_ID);
  Wire.send(0x40);
  Wire.send(0x00);
  Wire.endTransmission();
  update();
}

bool Nunchuk::update() {
  Serial.print("A");
  delay(1);
  Serial.print("B");
  Wire.requestFrom(NUNCHUK_DEVICE_ID, NUNCHUK_BUFFER_SIZE);
  int byte_counter = 0;
  Serial.print(byte_counter);
  while (Wire.available() && byte_counter < NUNCHUK_BUFFER_SIZE) {
    _buffer[byte_counter++] = decode_byte(Wire.receive());
    Serial.print(byte_counter);
  }
  Serial.print(byte_counter);
  Serial.print("C");
  request_data();
  Serial.print("D\n");
  return byte_counter == NUNCHUK_BUFFER_SIZE;
}

void Nunchuk::request_data() {
  Wire.beginTransmission(NUNCHUK_DEVICE_ID);
  Wire.send(0x00);
  Wire.endTransmission();
}

char Nunchuk::decode_byte(const char b) {
  return (b ^ 0x17) + 0x17;
}