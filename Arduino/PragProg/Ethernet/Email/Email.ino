#include <SPI.h>
#include <Ethernet.h>
#include "smtp_service.h"

const unsigned int SMTP_PORT = 25;
const unsigned int BAUD_RATE = 9600;

byte mac[]   = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte my_ip[] = { 192, 168, 2, 120 };

 // Insert IP of your SMTP server below!
byte smtp_server[] = { 0, 0, 0, 0 };

SmtpService smtp_service(smtp_server, SMTP_PORT);

void setup() {
  Ethernet.begin(mac, my_ip);
  Serial.begin(BAUD_RATE);
  delay(1000);
  Email email( // <label id="code.ethernet.init_mail"/>
    "arduino@example.com",
    "info@example.net",
    "Yet another subject",
    "Yet another body"
  );
  smtp_service.send_email(email);
}

void loop() {}

