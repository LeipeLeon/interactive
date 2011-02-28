#simplest ruby program to read from arduino serial, 
#using the SerialPort gem
#(http://rubygems.org/gems/serialport)
require 'rubygems'
require 'bundler'
require "serialport"

# params for serial port
# usaly in the form of /dev/tty.usbmodem*
port_str = "/dev/tty.usbmodem411"  #may be different for you
baud_rate = 9600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

#just read forever
while true do
  printf("%c", sp.getc)
end

sp.close                       #see note 1
