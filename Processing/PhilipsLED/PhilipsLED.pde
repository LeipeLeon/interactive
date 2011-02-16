// http://www.sparkfun.com/tutorials/152

import oscP5.*;              //  Load OSC P5 library
import netP5.*;              //  Load net P5 library
import processing.serial.*;  //  Load serial library

Serial arduinoPort;          //  Set arduinoPort as serial connection
OscP5 oscP5;                 //  Set oscP5 as OSC connection

slider s1;
slider s2;
slider s3;

int redLED = 0;              //  redLED lets us know if the LED is on or off
int [] led = new int [3];    //  Array allows us to add more toggle buttons in TouchOSC

void setup() {
  size(400,400);             // Processing screen size
  noStroke();                //  We don’t want an outline or Stroke on our graphics
  smooth();
  oscP5 = new OscP5(this,8000);  // Start oscP5, listening for incoming messages at port 8000
  arduinoPort = new Serial(this, Serial.list()[0], 9600);    // Set arduino to 9600 baud
  
  s1 = new slider(170,20,128, color(255,   0,   0));
  s2 = new slider(200,20,128, color(0  , 255,   0));
  s3 = new slider(230,20,128, color(0  , 0  , 255));
}

void draw() {
  background(50);              // Sets the background to a dark grey, can be 0-255
  s1.render();
  s2.render();
  s3.render();

  for (int i=0; i < led.length; i++) {
    fill(((led[i] == 0) ? 0 : 254),0,0);              // Fill rectangle with redLED amount
    ellipse(50, (60 * i) + 40, 50, 50);  // Created an ellipse at 50 pixels from the left...
                              // 50 pixels from the top and a width of 50 and height of 50 pixels
  }
}

void oscEvent(OscMessage theOscMessage) {      //  This runs whenever there is a new OSC message
  String addr = theOscMessage.addrPattern();   //  Creates a string out of the OSC message
  if(addr.indexOf("/1/toggle") !=-1) {         // Filters out any toggle buttons
    int i = int((addr.charAt(9) )) - 0x30;     // returns the ASCII number so convert into a real number by subtracting 0x30
    led[i]  = int(theOscMessage.get(0).floatValue());     //  Puts button value into led[i]
    // Button values can be read by using led[0], led[1], led[2], etc.
    writeToArduino(i, ((led[i] == 0) ? 128 : 254));
  }
  if(addr.indexOf("/1/fader") !=-1) {         // Filters out any toggle buttons
    int i = int((addr.charAt(8) ));// - 0x30;      // returns the ASCII number so convert into a real number by subtracting 0x30
    writeToArduino(i, int(theOscMessage.get(0).floatValue()));
  }
}

void writeToArduino(int clr, int val) {
  arduinoPort.write(byte(val));
  arduinoPort.write(clr);
  //println(val);
//  println(clr);

  if (82 == clr) {
    s1.setP(val-128);
  } else if (71 == clr) {
    s2.setP(val-128);
  } else if (66 == clr) {
    s3.setP(val-128);
  }
}


void serialEvent(Serial myPort) {
  // read a byte from the serial port:
//  print("Recieved: ");
  print(char(myPort.read()));
}
