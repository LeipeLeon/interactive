// Deriviated from http://www.sparkfun.com/tutorials/152
final int SLIDER  = 0;
final int LED = 1;

import oscP5.*;              //  Load OSC P5 library
import netP5.*;              //  Load net P5 library
import processing.serial.*;  //  Load serial library

Serial arduinoPort;          //  Set arduinoPort as serial connection
OscP5 oscP5;                 //  Set oscP5 as OSC connection
NetAddress myRemoteLocation; //  oscP5 remote address

slider s1;
slider s2;
slider s3;

int redLED = 0;              //  redLED lets us know if the LED is on or off
int [] led = new int [3];    //  Array allows us to add more toggle buttons in TouchOSC
color [] ledColor = new color [3] ; //{color(255,   0,   0),  color(0  , 255,   0), color(0  , 0  , 255)};
boolean forceRedraw = true;

void setup() {
  size(400,400);             // Processing screen size
  noStroke();                //  We don’t want an outline or Stroke on our graphics
  smooth();
  oscP5 = new OscP5(this,8000);  // Start oscP5, listening for incoming messages at port 8000
  myRemoteLocation = new NetAddress("192.168.1.14",9000); // iPad IP Address
  arduinoPort = new Serial(this, Serial.list()[0], 9600); // Set arduino to 9600 baud
  
  s1 = new slider(170,20,128, color(255,   0,   0));
  s2 = new slider(200,20,128, color(0  , 255,   0));
  s3 = new slider(230,20,128, color(0  , 0  , 255));
  writeBackToOSC('R', 1);
  writeBackToOSC('G', 1);
  writeBackToOSC('B', 1);
}

void draw() {
  if (forceRedraw) {
    forcedRedraw();
  }
}

void forcedRedraw() {
  background(50);              // Sets the background to a dark grey, can be 0-255
  s1.render();
  s2.render();
  s3.render();

  for (int i=0; i < ledColor.length; i++) {
    fill(ledColor[i]);              // Fill elipse with ledColor amount
    ellipse(50, (60 * i) + 40, 50, 50);
  }
  forceRedraw = false;
}  

void oscEvent(OscMessage theOscMessage) {      //  This runs whenever there is a new OSC message
  String addr = theOscMessage.addrPattern();   //  Creates a string out of the OSC message
  print("M:");
  println(int(theOscMessage.get(0).floatValue()));
  if(addr.indexOf("/1/toggle") !=-1) {         // Filters out any toggle buttons
    int i = int((addr.charAt(9) )) +0x20 ;     // returns the lowercase 
    // Button values can be read by using led[0], led[1], led[2], etc.
    writeToArduino(i, int(theOscMessage.get(0).floatValue()));
  }
  if(addr.indexOf("/1/fader") !=-1) {         // Filters out any fader buttons
    int i = int((addr.charAt(8) ));//  // make it lowercase by adding 
    writeToArduino(i, int(theOscMessage.get(0).floatValue()));
    writeBackToOSC(i, int(theOscMessage.get(0).floatValue()));
  }
  forceRedraw = true;
}

void writeBackToOSC(int clr, int val) {
  OscMessage myMessage = new OscMessage("/1/toggle"+char(clr));
  myMessage.add(val); /* add an float to the osc message */
  oscP5.send(myMessage, myRemoteLocation);  
}

void writeToArduino(int clr, int val) {

  // Feedback to the screen
  if ('R' == clr) {
    ledColor[0] = color((val-128)*2,0,0);
    s1.setP(val-128); 
  } else if ('G' == clr) {
    ledColor[1] = color(0,(val-128)*2,0);
    s2.setP(val-128);
  } else if ('B' == clr) {
    ledColor[2] = color(0,0,(val-128)*2);
    s3.setP(val-128);
  } 

  if ('r' == clr) {
    val = s1.toggle();
    clr = 'R';
  } else if ('g' == clr) {
    val = s2.toggle();
    clr = 'G';
  } else if ('b' == clr) {
    val = s3.toggle();
    clr = 'B';
  }

  arduinoPort.write(byte(val));
  arduinoPort.write(clr);
  print(char(clr));
  print(":");
  println(val);
}


void serialEvent(Serial myPort) {
  // read a byte from the serial port:
//  print("Recieved: ");
//  print(char(myPort.read()));
}
