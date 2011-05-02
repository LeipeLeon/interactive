// START:init_serial
import processing.serial.*;

final int LINE_FEED = 10;
final int MAX_SAMPLES = 16;

Serial arduinoPort;
SensorDataBuffer sensorData = new SensorDataBuffer(MAX_SAMPLES);
// END:init_serial

// START:init_constants
final int WIDTH = 500;
final int HEIGHT = 500;
final int BAUD_RATE = 19200;
final int X_AXIS_MIN = 300;
final int X_AXIS_MAX = 700;
final int Y_AXIS_MIN = 300;
final int Y_AXIS_MAX = 700;
final int Z_AXIS_MIN = 300;
final int Z_AXIS_MAX = 700;
final int MIN_SCALE = 5;
final int MAX_SCALE = 128;
final float MX = 2.0 / (X_AXIS_MAX - X_AXIS_MIN);
final float MY = 2.0 / (Y_AXIS_MAX - Y_AXIS_MIN);
final float MZ = 2.0 / (Z_AXIS_MAX - Z_AXIS_MIN);
final float BX = 1.0 - MX * X_AXIS_MAX;
final float BY = 1.0 - MY * Y_AXIS_MAX;
final float BZ = 1.0 - MZ * Z_AXIS_MAX;
// END:init_constants

// START:init_variables
int xpos = WIDTH / 2;
int ypos = HEIGHT / 2;
int scale = 90;

float xrotate = 0.0;
float yrotate = 0.0;
float zrotate = 0.0;
// END:init_variables

// START:setup
void setup() {
  size(WIDTH, HEIGHT, P3D);
  noStroke(); 
  colorMode(RGB, 1); // <label id="code.nunchuk.cube_color"/>
  background(0);
  println(Serial.list());
  arduinoPort = new Serial(this, Serial.list()[0], BAUD_RATE);
  arduinoPort.bufferUntil(LINE_FEED);
}
// END:setup

// START:draw
void draw() { 
  background(0);
  pushMatrix();
  
  translate(xpos, ypos, -30); // <label id="code.nunchuk.begin_rotate"/>
  rotateX(yrotate); 
  rotateY(xrotate); 
  rotateZ(zrotate);  // <label id="code.nunchuk.end_rotate"/>
  scale(scale); // <label id="code.nunchuk.scale_cube"/>
  
  beginShape(QUADS);
  fill(0, 1, 1); vertex(-1,  1,  1);
  fill(1, 1, 1); vertex( 1,  1,  1);
  fill(1, 0, 1); vertex( 1, -1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);

  fill(1, 1, 1); vertex( 1,  1,  1);
  fill(1, 1, 0); vertex( 1,  1, -1);
  fill(1, 0, 0); vertex( 1, -1, -1);
  fill(1, 0, 1); vertex( 1, -1,  1);

  fill(1, 1, 0); vertex( 1,  1, -1);
  fill(0, 1, 0); vertex(-1,  1, -1);
  fill(0, 0, 0); vertex(-1, -1, -1);
  fill(1, 0, 0); vertex( 1, -1, -1);

  fill(0, 1, 0); vertex(-1,  1, -1);
  fill(0, 1, 1); vertex(-1,  1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);
  fill(0, 0, 0); vertex(-1, -1, -1);

  fill(0, 1, 0); vertex(-1,  1, -1);
  fill(1, 1, 0); vertex( 1,  1, -1);
  fill(1, 1, 1); vertex( 1,  1,  1);
  fill(0, 1, 1); vertex(-1,  1,  1);

  fill(0, 0, 0); vertex(-1, -1, -1);
  fill(1, 0, 0); vertex( 1, -1, -1);
  fill(1, 0, 1); vertex( 1, -1,  1);
  fill(0, 0, 1); vertex(-1, -1,  1);
  endShape();
  
  popMatrix(); 
} 
// END:draw

// START:serial_event
void serialEvent(Serial port) {
  final String arduinoData = port.readStringUntil(LINE_FEED);

  if (arduinoData != null) {
    final int[] data = int(split(trim(arduinoData), ' '));
    if (data.length == 7) {
      xpos = int(map(data[0], 0x1e, 0xe1, 0, WIDTH)); // <label id="code.nunchuk.map_x"/>
      ypos = int(map(data[1], 0x1d, 0xdf, HEIGHT, 0));
      
      if (data[5] == 1) scale++; // <label id="code.nunchuk.start_scale"/>
      if (data[6] == 1) scale--;
      if (scale < MIN_SCALE) scale = MIN_SCALE;
      if (scale > MAX_SCALE) scale = MAX_SCALE; // <label id="code.nunchuk.end_scale"/>
      
      sensorData.addData(data[2], data[3], data[4]);
      
      final float gx = MX * sensorData.getX() + BX;
      final float gy = MY * sensorData.getY() + BY;
      final float gz = MZ * sensorData.getZ() + BZ;
      
      xrotate = atan2(gx, sqrt(gy * gy + gz * gz));
      yrotate = atan2(gy, sqrt(gx * gx + gz * gz));
      zrotate = atan2(sqrt(gx * gx + gy * gy), gz);
    }
  }
}
// END:serial_event

