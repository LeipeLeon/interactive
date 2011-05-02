#include "arduino-serial.h"

int serialport_writebyte(int fd, uint8_t b) {
  int n = write(fd, &b, 1);
  return (n != 1) ? -1 : 0;
}

int serialport_write(int fd, const char* str) {
  int len = strlen(str);
  int n = write(fd, str, len);
  return (n != len) ? -1 : 0;
}

int serialport_read_until(int fd, char* buf, char until) {
  char b[1];
  int i = 0;
  do { 
    int n = read(fd, b, 1);
    if (n == -1) 
      return -1;
      if (n == 0) {
        usleep(10 * 1000);
        continue;
      }
      buf[i++] = b[0];
  } while (b[0] != until);

  buf[i] = 0;
  return 0;
}

int serialport_init(const char* serialport, int baud) {
  int fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) {
    perror("init_serialport: Unable to open port");
    return -1;
  }
    
  struct termios toptions;
  if (tcgetattr(fd, &toptions) < 0) {
    perror("init_serialport: Couldn't get term attributes");
    return -1;
  }

  speed_t brate = baud;
  switch(baud) {
    case 4800:   brate = B4800;   break;
    case 9600:   brate = B9600;   break;
    case 19200:  brate = B19200;  break;
    case 38400:  brate = B38400;  break;
    case 57600:  brate = B57600;  break;
    case 115200: brate = B115200; break;
  }
  cfsetispeed(&toptions, brate);

  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  toptions.c_cflag &= ~CRTSCTS;
  toptions.c_cflag |= CREAD | CLOCAL;
  toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
  toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  toptions.c_oflag &= ~OPOST;

  toptions.c_cc[VMIN]  = 0;
  toptions.c_cc[VTIME] = 20;
    
  if (tcsetattr(fd, TCSANOW, &toptions) < 0) {
    perror("init_serialport: Couldn't set term attributes");
    return -1;
  }

  return fd;
}
