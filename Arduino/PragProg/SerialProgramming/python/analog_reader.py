import sys
import time
import serial

if len(sys.argv) != 2:
  print "You have to pass the name of a serial port."
  sys.exit(1)

serial_port = sys.argv[1]
arduino = serial.Serial( # <label id="code.appendix.python_serial"/>
  serial_port,
  9600,
  serial.EIGHTBITS,
  serial.PARITY_NONE,
  serial.STOPBITS_ONE
)
time.sleep(2)

while 1:
  arduino.write('a0')
  line = arduino.readline().rstrip()
  print line
