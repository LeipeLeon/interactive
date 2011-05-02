#ifndef __SMTP_SERVICE__H_
#define __SMTP_SERVICE__H_

#include "email.h"

class SmtpService {
  byte*        _smtp_server;
  unsigned int _port;
 
  void read_response(Client& client) { // <label id="code.ethernet.read_response"/>
    delay(4000);
    while (client.available()) {
      const char c = client.read();
      Serial.print(c);
    }
  }

  void send_line(Client& client, String line) { // <label id="code.ethernet.send_line"/>
    const unsigned int MAX_LINE = 256;
    char buffer[MAX_LINE];
    line.toCharArray(buffer, MAX_LINE);
    Serial.println(buffer);
    client.println(buffer);
    read_response(client);
  }

  public:
  
  SmtpService( // <label id="code.ethernet.smtp_constructor"/>
    byte*              smtp_server,
    const unsigned int port) : _smtp_server(smtp_server), 
                               _port(port) {}
                               
  void send_email(const Email& email) { // <label id="code.ethernet.send_mail"/>
    Client client(_smtp_server, _port);
    Serial.print("Connecting...");
  
    if (!client.connect()) {
      Serial.println("connection failed.");
    } else {
      Serial.println("connected.");
      read_response(client);
      send_line(client, String("helo"));
      send_line(
        client,
        String("mail from: <") + email.getFrom() + String(">")
      );
      send_line(
        client,
        String("rcpt to: <") + email.getTo() + String(">")
      );
      send_line(client, String("data"));
      send_line(client, String("from: ") + email.getFrom());
      send_line(client, String("to: ") + email.getTo());
      send_line(client, String("subject: ") + email.getSubject());
      send_line(client, String(""));
      send_line(client, email.getBody());
      send_line(client, String("."));    
      send_line(client, String("quit"));    
      client.println("Disconnecting.");
      client.stop();
    }
  }
};

#endif
