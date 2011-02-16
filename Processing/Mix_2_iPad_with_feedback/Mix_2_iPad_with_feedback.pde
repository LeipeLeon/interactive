/**
 * 2011-02-17 @leipeleon downloaded from http://www.thebox.myzen.co.uk/Mac_Apps/Processing.html
 */
/**
 * TouchOSCmultitoggle
 * 
 * Example displaying values received from
 * the "Simple" layout (Page4) multitoggle
 * By Mike Cook
 * http://www.thebox.myzen.co.uk
 *
 */

import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;

boolean multiFadeNeedsRedraw = true;
float [][] multiFade = new float [2][17]; 


void setup() {
  size(290,360);
  frameRate(25);
  background(0);
  /* start oscP5, listening for incoming messages at port 8000 */
  oscP5 = new OscP5(this,8000);
  // set the local IP address on the iPod to this
  myRemoteLocation = new NetAddress("192.168.1.14",9000);
  // by choosig a static IP address make sure it is in the same domain as the host
}

void oscEvent(OscMessage theOscMessage) {
  String addr = theOscMessage.addrPattern();     
  //  println(addr);   // uncomment for seeing the raw message

  if(addr.indexOf("/2/multifader2/") !=-1) { // the bottom 16 slider fader
    String list[] = split(addr,'/');
    int x = int(list[3]);
    multiFade[1][x]  = theOscMessage.get(0).floatValue();
    // invert the value and send it back to the multi touch
    multiFade[0][x]  = 1- multiFade[1][x];
    OscMessage myMessage = new OscMessage("/2/multifader1/"+list[3]);
    myMessage.add(multiFade[0][x]); /* add an float to the osc message */
    oscP5.send(myMessage, myRemoteLocation);
    multiFadeNeedsRedraw = true;
  }
  if(addr.indexOf("/2/multifader1/") !=-1) { // the top 16 slider fader
    String list[] = split(addr,'/');
    int x = int(list[3]);
    multiFade[0][x]  = theOscMessage.get(0).floatValue();
    // invert the value and send it back to the multi touch
    multiFade[1][x]  = 1- multiFade[0][x];
    OscMessage myMessage = new OscMessage("/2/multifader2/"+list[3]);
    myMessage.add(multiFade[1][x]); /* add an float to the osc message */
    oscP5.send(myMessage, myRemoteLocation);
    multiFadeNeedsRedraw = true;
  }
}

void draw() {
  if(multiFadeNeedsRedraw == true) redrawmultiFade();  // only redraw the screen if we need to
}

// Update the screen image
void redrawmultiFade() { // redraw the screen
  strokeWeight(2);
  noFill();
  stroke(250,50,50);
  rect(15, 15, 260, 160);  // red outline

  // do top (red) faders
  for(int x=1 ; x<17; x++) {
    noStroke();
    fill(40,40,40);
    rect( x*16+4, 16, 12, 157);   // blank rectangle
    fill(250,50,50,60);
    rect( x*16+4, 15+(1-multiFade[0][x])*145, 12, 80-(1-multiFade[0][x])*145); 
    fill(250,50,50); // do the solid square
    rect( x*16+4, 15+(1-multiFade[0][x])*145, 12, 12);
  }  

  // do bottom (green) faders 
  noFill(); 
  stroke(50,250,50);
  rect(15, 190, 260, 160);  // green outline
  for(int x=1 ; x<17; x++) {
    noStroke();
    fill(40,40,40);
    rect( x*16+4, 191, 12, 157);   // blank rectangle
    fill(50,250,50,60);
    rect( x*16+4, 191+(1-multiFade[1][x])*145, 12, 80-(1-multiFade[1][x])*145); 
    fill(50,250,50); // do the solid square
    rect( x*16+4, 191+(1-multiFade[1][x])*145, 12, 12);
  }  

  multiFadeNeedsRedraw = false;  // we have now redrawn it, don't do it again until we have another OSC message
}

