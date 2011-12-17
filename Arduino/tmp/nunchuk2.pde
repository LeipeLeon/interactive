// http://hacknmod.com/hack/how-to-cheap-accelerometer-using-wii-nunchuck/
//Three analog sensors, formatted and sending out of the Arduino. 
// Processing takes them and does a simple display on screen.

// From ITP at NYU - http://itp.nyu.edu/physcomp/

//Arduino Code - read from 3 different analog inputs

int an1, an2, an3 = 0;

void setup() {
  Serial.begin(19200);
}

void loop() {
  an1 = analogRead(0);
  delay(5); 
  an2 = analogRead(1);
  delay(5); 
  an3 = analogRead(2);
  Serial.print("X");
  Serial.println(an1,DEC);
  Serial.print("Y");
  Serial.println(an2,DEC);
  Serial.print("Z");
  Serial.println(an3,DEC);
  delay(15);               
}

//Processing Code

import processing.serial.*;

String buff = "";
int val = 0;
int NEWLINE = 10;
int xPos,yPos,zPos = 0;
int displaySize = 2;
int an1, an2, an3;

Serial port;

void setup(){
  background(80);
  size(800,600);
  smooth();

  port = new Serial(this, Serial.list()[0], 19200);
}

void draw(){
  // new background over old
  fill(80,5);
  noStroke();
  rect(0,0,width,height);

  // wipe out a small area in front of the new data
  fill(80);
  rect(xPos+displaySize,0,50,height);

  // check for serial, and process
  while (port.available() > 0) {
    serialEvent(port.read());
  }
}


void serialEvent(int serial) { 
  if(serial != '\n') { 
    buff += char(serial);
  } else {
    int curX = buff.indexOf("X");
    int curY = buff.indexOf("Y");
    int curZ = buff.indexOf("Z");

    if(curX >=0){
      String val = buff.substring(curX+1);
      an1 = Integer.parseInt(val.trim());

      xPos++;
      if(xPos > width) xPos = 0;

      sensorTic(xPos,an1+20);
    }    
    if(curY >=0){
      String val = buff.substring(curY+1);
      an2 = Integer.parseInt(val.trim());

      yPos++;
      if(yPos > width) yPos = 0;

      sensorTic(yPos,an2-255);
    }
    if(curZ >=0){
      String val = buff.substring(curZ+1);
      an3 = Integer.parseInt(val.trim());

      zPos++;
      if(zPos > width) zPos = 0;

      sensorTic(zPos,an3-255);
    }

    // Clear the value of "buff"
    buff = "";
  }
}

void sensorTic(int x, int y){
  stroke(0,0,255);
  fill(0,0,255);
  ellipse(x,y,displaySize,displaySize);
}