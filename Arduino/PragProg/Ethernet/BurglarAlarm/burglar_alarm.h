#ifndef __BURGLAR_ALARM_H__
#define __BURGLAR_ALARM_H__

#include "pir_sensor.h"
#include "smtp_service.h"

class BurglarAlarm {
  PassiveInfraredSensor _pir_sensor;
  SmtpService           _smtp_service;

  void send_alarm() {
    Email email(
      "arduino@example.com",
      "info@example.net",
      "Intruder Alert!",
      "Someone's moving in your living room!"
    );
    _smtp_service.send_email(email);
  }
  
  public:
  
  BurglarAlarm( // <label id="code.ethernet.burglar_alarm_constructor"/>
    const PassiveInfraredSensor& pir_sensor,
    const SmtpService&           smtp_service) :
      _pir_sensor(pir_sensor),
      _smtp_service(smtp_service)
  {
  }
  
  void check() {
    Serial.println("Checking");
    if (_pir_sensor.motion_detected()) {
      Serial.println("Intruder detected!");
      send_alarm();
    }
  }
};

#endif
