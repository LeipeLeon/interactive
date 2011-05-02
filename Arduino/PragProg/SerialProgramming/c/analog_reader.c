#include <stdio.h>
#include <unistd.h>
#include "arduino-serial.h"

#define MAX_LINE 256

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("You have to pass the name of a serial port.\n");
    return -1;
  }

  int baudrate = B9600;
  int arduino = serialport_init(argv[1], baudrate); // <label id="code.appendix.serialport_init"/>
  if (arduino == -1) {
    printf("Could not open serial port %s.\n", argv[1]);
    return -1;
  }
  sleep(2);

  char line[MAX_LINE];
  while (1) {
    int rc = serialport_write(arduino, "a0\n"); // <label id="code.appendix.serialport_write"/>
    if (rc == -1) {
      printf("Could not write to serial port.\n");
    } else {
      serialport_read_until(arduino, line, '\n'); // <label id="code.appendix.serialport_read"/>
      printf("%s", line);
    }
  }
  return 0;
}
