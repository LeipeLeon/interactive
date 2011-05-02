#ifndef __PIR_SENSOR__H__
#define __PIR_SENSOR__H__

#include <WProgram.h>

class PassiveInfraredSensor {
  int _input_pin;

  public:

  PassiveInfraredSensor(const int input_pin) {
    _input_pin = input_pin;
    pinMode(_input_pin, INPUT);
  }
  
  const bool motion_detected() const {
    return digitalRead(_input_pin) == HIGH;
  }
};

#endif
