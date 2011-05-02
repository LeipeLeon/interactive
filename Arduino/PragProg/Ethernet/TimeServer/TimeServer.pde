#include <SPI.h>
#include <Ethernet.h>

const unsigned int DAYTIME_PORT = 13;
const unsigned int BAUD_RATE = 9600;

byte mac[]         = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte my_ip[]       = { 192, 168, 2, 120 };
byte time_server[] = { 192, 43, 244, 18 }; // time.nist.gov

Client client(time_server, DAYTIME_PORT); // <label id="code.ethernet.client"/>

void setup() {
  Ethernet.begin(mac, my_ip); // <label id="code.ethernet.init"/>
  Serial.begin(BAUD_RATE);
}

void loop() {
  delay(1000);
  Serial.print("Connecting...");
  
  if (!client.connect()) { // <label id="code.ethernet.connect"/>
    Serial.println("connection failed.");
  } else {
    Serial.println("connected.");
    delay(1000);
  
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
    
    Serial.println("Disconnecting.");
    client.stop();
  }
}

