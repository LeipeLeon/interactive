// START:apple_remote_class
#include <IRremote.h>

class AppleRemote {
  
  enum {
    CMD_LEN = 32,
    UP      = 0x77E15061,
    DOWN    = 0x77E13061,
    PLAY    = 0x77E1A05E,
    PREV    = 0x77E1905E,
    NEXT    = 0x77E1605E,
    MENU    = 0x77E1C05E
  };
  
  IRsend mac;

  void send_command(const long command) {
    mac.sendNEC(command, CMD_LEN);
  }
  
  public:
  
  void menu() { send_command(MENU); }
  void play() { send_command(PLAY); }
  void prev() { send_command(PREV); }
  void next() { send_command(NEXT); }
  void up()   { send_command(UP);   }
  void down() { send_command(DOWN); }
};
// END:apple_remote_class

// START:apple_remote_sample
AppleRemote apple_remote;
const unsigned int BAUD_RATE = 9600;

void setup() {
  Serial.begin(BAUD_RATE);
}

void loop() {
  if (Serial.available()) {
    const char command = Serial.read();
    switch(command) {
      case 'm':
        apple_remote.menu();
        break;      
      case 'u':
        apple_remote.up();
        break;      
      case 'd':
        apple_remote.down();
        break;      
      case 'l':
        apple_remote.prev();
        break;      
      case 'r':
        apple_remote.next();
        break;      
      case 'p':
        apple_remote.play();
        break;      
      default:
        break;
    }
  }
}
// END:apple_remote_sample

