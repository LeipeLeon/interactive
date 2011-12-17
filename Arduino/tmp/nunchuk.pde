// http://hacknmod.com/hack/how-to-cheap-accelerometer-using-wii-nunchuck/
// This example reads in a single byte value from 0 to 255 and graphs it.

/////////////////////////////////////////
// Basic serial communication code
// by Chang Soo Lee
// ITP, NYU
// Created 11/27/2005
/////////////////////////////////////////

import processing.serial.*;
Serial myPort;
int serial = 1; 
PFont font;
int numH = 370;  

void setup () {
  size(270, 440);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  // Load the font. Fonts must be placed within the data 
  // directory of your sketch. Use Tools > Create Font 
  // to create a distributable bitmap font. 
  // For vector fonts, use the createFont() function. 

  font = loadFont("ArialMT-48.vlw"); 
  smooth(); 
}

void draw () {
  background(255);

  if (myPort.available() > 0) {
    serial = myPort.read();
    serialEvent();
  } 

  line(70,70,70,370);
  line(70,370,200,370);
  fill(0);
  textFont(font, 11); 
  text("Sensor\nValue",22,80);
  text("Analog Input", 95, 390);
  text(serial,25,110);
  noFill();
}

void serialEvent(){
  if(serial>1){
    rect(120,numH-serial, 20, serial);
  }
}
