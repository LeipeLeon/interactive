// START:game_serial
import processing.serial.*;
Serial arduinoPort;
// END:game_serial

// START:game_constants
final int COLUMNS = 7;
final int ROWS = 4;
final int BALL_RADIUS = 8;
final int BALL_DIAMETER = BALL_RADIUS * 2;
final int MAX_VELOCITY = 8;
final int PADDLE_WIDTH = 60;
final int PADDLE_HEIGHT = 15;
final int BRICK_WIDTH = 40;
final int BRICK_HEIGHT = 20;
final int MARGIN = 10;
final int WIDTH = COLUMNS * BRICK_WIDTH + 2 * MARGIN;
final int HEIGHT = 300;
final int X_AXIS_MIN = 252;
final int X_AXIS_MAX = 443;
final int LINE_FEED = 10;
final int BAUD_RATE = 19200;
// END:game_constants

// START:game_objects
int px, py;
int vx, vy;
int xpos = WIDTH / 2;
int[][] bricks = new int[COLUMNS][ROWS];
// END:game_objects

// START:game_states
boolean buttonPressed = false;
boolean paused = true;
boolean done = true;
// END:game_states

// START:game_init
void setup() {
  size(WIDTH, HEIGHT);
  noCursor();
  textFont(loadFont("Verdana-Bold-36.vlw"));
  initGame();  
  println(Serial.list());
  arduinoPort = new Serial(this, Serial.list()[0], BAUD_RATE);
  arduinoPort.bufferUntil(LINE_FEED);
}

void initGame() {
  initBricks();
  initBall();
}

void initBricks() {
  for (int x = 0; x < COLUMNS; x++)
    for (int y = 0; y < ROWS; y++ )
      bricks[x][y] = 1;
}

void initBall() {
  px = width / 2;
  py = height / 2;
  vx = int(random(-MAX_VELOCITY, MAX_VELOCITY));
  vy = -2;
}
// END:game_init

// START:game_main
void draw() {
  background(0);
  stroke(255);
  strokeWeight(3);
  
  done = drawBricks();
  if (done) {
    paused = true;
    printWinMessage();
  }
  
  if (paused)
    printPauseMessage();
  else
    updateGame();
  
  drawBall();
  drawPaddle();  
}
// END:game_main

// START:game_draw_objects
boolean drawBricks() {
  boolean allEmpty = true;
  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (bricks[x][y] > 0) {
        allEmpty = false;
        fill(0, 0, 100 + y * 8);
        rect(
          MARGIN + x * BRICK_WIDTH,
          MARGIN + y * BRICK_HEIGHT,
          BRICK_WIDTH,
          BRICK_HEIGHT
        );
      }
    }
  }
  return allEmpty;
}

void drawBall() {
  strokeWeight(1);
  fill(128, 0, 0);
  ellipse(px, py, BALL_DIAMETER, BALL_DIAMETER);
}

void drawPaddle() {
  int x = xpos - PADDLE_WIDTH / 2;
  int y = height - (PADDLE_HEIGHT + MARGIN);
  strokeWeight(1);
  fill(128);
  rect(x, y, PADDLE_WIDTH, PADDLE_HEIGHT);
}
// END:game_draw_objects

// START:game_messages
void printWinMessage() {
  fill(255);
  textSize(36);
  textAlign(CENTER);
  text("YOU WIN!", width / 2, height * 2 / 3);
}

void printPauseMessage() {
  fill(128);
  textSize(16);
  textAlign(CENTER);
  text("Press Button to Continue", width / 2, height * 5 / 6);
}
// END:game_messages

// START:game_update
void updateGame() {
  if (ballDropped()) {
    initBall();
    paused = true;
  } else {
    checkBrickCollision();
    checkWallCollision();
    checkPaddleCollision();
    px += vx;
    py += vy;
  }
}
// END:game_update

// START:game_collision
boolean ballDropped() {
  return py + vy > height - BALL_RADIUS;
}

boolean inXRange(final int row, final int v) {
  return px + v > row * BRICK_WIDTH && 
         px + v < (row + 1) * BRICK_WIDTH + BALL_DIAMETER;
}

boolean inYRange(final int col, final int v) {
  return py + v > col * BRICK_HEIGHT &&
         py + v < (col + 1) * BRICK_HEIGHT + BALL_DIAMETER;
}

void checkBrickCollision() {
  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      if (bricks[x][y] > 0) {
        if (inXRange(x, vx) && inYRange(y, vy)) {
          bricks[x][y] = 0;
          if (inXRange(x, 0)) // Hit top or bottom of brick.
            vy = -vy;
          if (inYRange(y, 0)) // Hit left or right side of brick.
            vx = -vx; 
        }
      }
    }
  }
}

void checkWallCollision() {
  if (px + vx < BALL_RADIUS || px + vx > width - BALL_RADIUS)
    vx = -vx;

  if (py + vy < BALL_RADIUS || py + vy > height - BALL_RADIUS)
    vy = -vy;
}

void checkPaddleCollision() {
  final int cx = xpos;
  if (py + vy >= height - (PADDLE_HEIGHT + MARGIN + 6) &&
      px >= cx - PADDLE_WIDTH / 2 &&
      px <= cx + PADDLE_WIDTH / 2)
  {
    vy = -vy;
    vx = int(
           map(
             px - cx,
             -(PADDLE_WIDTH / 2), PADDLE_WIDTH / 2,
             -MAX_VELOCITY,
             MAX_VELOCITY
           )
         );
  }  
}
// END:game_collision

// START:game_controller
void serialEvent(Serial port) {
  final String arduinoData = port.readStringUntil(LINE_FEED);

  if (arduinoData != null) {
    final int[] data = int(split(trim(arduinoData), ' ')); // <label id="code.motion.controller_data"/>
    if (data.length == 4) {
      buttonPressed = (data[3] == 1);
      if (buttonPressed) {
        paused = !paused;
        if (done) {
          done = false;
          initGame();
        }
      }
      
      if (!paused)
        xpos = int(map(data[0], X_AXIS_MIN, X_AXIS_MAX, 0, WIDTH)); // <label id="code.motion.xpos"/>
    }
  }
}
// END:game_controller

