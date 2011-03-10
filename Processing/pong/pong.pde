// http://processing.org/discourse/yabb2/YaBB.pl?num=1239235781

float ballx = width - 100;
float bally = height / 2;
float yspeed = 6;
float xspeed = 6;
int leftscore = 0;
PFont font;
int x = 0;
int pause;
int tmpscore = leftscore;
int menu = 1;

void setup() {
  size(600, 500, P2D);
  font = loadFont("font.vlw");
  background(0);
  fill(255);
  noStroke();
  

}

void draw() {

  background(0);
  ball();
  paddle();
  action();
  textFont(font, 32);
  textAlign(CENTER);
  text(leftscore, 300, 30);
  if(menu == 1) {
    background(0);
    noLoop();
    textFont(font, 32);
    textAlign(CENTER);
    text("Click to Begin", 300, 250);
    
    
   } 
}

void ball() {
  ballx += xspeed;
  bally += yspeed;
  if(ballx <= 0 || ballx >= width - 10) {
    xspeed = -xspeed;
  }
  if(bally <= 0 || bally >= height - 10) {
    yspeed = -yspeed;
  }
  fill(255);
  rect(ballx, bally, 10, 10);
}

void paddle() {
  rectMode(CENTER);
  rect(30, mouseY, 10, 60);
}

void action() {
  if(ballx <= 35) {
    if (bally >= mouseY - 30 && bally <= mouseY) {
      xspeed = -xspeed;
      
      leftscore++;
    }
    if(bally <= mouseY + 30 && bally > mouseY) {
      xspeed = -xspeed;
      leftscore++;
    }
  }
  if(ballx <=20) {
    reset();
  }
} 

void reset() {
  ballx = width - 100;
  bally = height /2;
  xspeed = 5;
  yspeed = 5;
  leftscore = 0;
  menu = 1;
}

void keyPressed() {
  if(key == 'p' || key == 'P') {
    if(pause == 0) {
      noLoop();
      pause = 1;
      textFont(font, 32);
      textAlign(CENTER);
      text("PAUSED", 300, 250);
    }
    else {
      loop();
      pause = 0;
    }
  
  }
  if (key == 'r' || key == 'R') {
    reset();
  }
}
void mouseClicked() {
  if(menu==1) {
    loop();
    menu = 0;
  }
}

