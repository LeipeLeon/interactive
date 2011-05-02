// START:ir_proxy
#include <SPI.h>
#include <Ethernet.h>
#include <IRremote.h>

class InfraredProxy {
  IRsend _infrared_sender;

  void read_line(Client& client, char* buffer, const int buffer_length) { // <label id="code.remote_control.read_line"/>
    int buffer_pos = 0;
    while (client.available() && (buffer_pos < buffer_length - 1)) {
      const char c = client.read();
      if (c == '\n')
        break;
      if (c != '\r')
        buffer[buffer_pos++] = c;
    }
    buffer[buffer_pos] = '\0';
  }

  bool send_ir_data(const char* protocol, const int bits, const long value) { // <label id="code.remote_control.send_ir_data"/>
    bool result = true;
    if (!strcasecmp(protocol, "NEC"))
      _infrared_sender.sendNEC(value, bits);
    else if (!strcasecmp(protocol, "SONY"))
      _infrared_sender.sendSony(value, bits);
    else if (!strcasecmp(protocol, "RC5"))
      _infrared_sender.sendRC5(value, bits);
    else if (!strcasecmp(protocol, "RC6"))
      _infrared_sender.sendRC6(value, bits);
    else
      result = false;
    return result;
  }
  
  bool handle_command(char* line) { // <label id="code.remote_control.handle_command"/>
    strsep(&line, " "); // <label id="code.remote_control.strip_get"/>
    char* path = strsep(&line, " "); // <label id="code.remote_control.strip_http"/>

    char* args[3];
    for (char** ap = args; (*ap = strsep(&path, "/")) != NULL;) // <label id="code.remote_control.parse_begin"/>
      if (**ap != '\0')
        if (++ap >= &args[3])
          break; // <label id="code.remote_control.parse_end"/>
    const int  bits = atoi(args[1]);
    const long value = atol(args[2]);    
    return send_ir_data(args[0], bits, value);
  }
  
  public:
  
  void receive_from_server(Server server) {
    const int MAX_LINE = 256;
    char line[MAX_LINE];
    Client client = server.available(); // <label id="code.remote_control.server_available"/>
    if (client) {
      while (client.connected()) {
        if (client.available()) { // <label id="code.remote_control.client_available"/>
          read_line(client, line, MAX_LINE);
          Serial.println(line);
          if (line[0] == 'G' && line[1] == 'E' && line[2] == 'T')
            handle_command(line);
          if (!strcmp(line, "")) {
            client.println("HTTP/1.1 200 OK\n");
            break;
          }
        }
      }
      delay(1);
      client.stop();
    }
  }  
};
// END:ir_proxy

// START:main
const unsigned int PROXY_PORT = 80;
const unsigned int BAUD_RATE = 9600;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 2, 42 };

Server server(PROXY_PORT);
InfraredProxy ir_proxy;

void setup() {
  Serial.begin(BAUD_RATE);
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {
  ir_proxy.receive_from_server(server);
}
// END:main

