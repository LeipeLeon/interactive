// START:init_sonar
import processing.serial.*;

final int WIDTH = 1000;
final int HEIGHT = 1000;
final int xCenter = WIDTH / 2;
final int yCenter = HEIGHT / 2;
final int LINE_FEED = 10;

Serial arduinoPort;
SensorData sensorData;
int degree = 0;
int radius = 0;
// END:init_sonar

// START:arduino_communication
void setup() {
  size(WIDTH, HEIGHT);
  println(Serial.list());
  String arduinoPortName = Serial.list()[0];
  arduinoPort = new Serial(this, arduinoPortName, 9600); // <label id="code.input.serial_port"/>
  arduinoPort.bufferUntil(LINE_FEED);
}

void serialEvent(Serial port) {
  sensorData = getSensorData();
  if (sensorData != null) {
    println("Temperature: " + sensorData.getTemperature());
    println("Distance: " + sensorData.getDistance());
    radius = min(300, int(sensorData.getDistance() * 2));
  }
}

SensorData getSensorData() {
  SensorData result = null;
  if (arduinoPort.available() > 0) { // <label id="code.input.data_available"/>
    final String arduinoOutput = arduinoPort.readStringUntil(LINE_FEED);
    result = parseArduinoOutput(arduinoOutput);
  }
  return result;
}

SensorData parseArduinoOutput(final String arduinoOutput) {
  SensorData result = null;
  if (arduinoOutput != null) {
    final int[] data = int(split(trim(arduinoOutput), ',')); // <label id="code.input.parse_output"/>
    if (data.length == 2)
      result = new SensorData(data[0] / 100.0, data[1] / 100.0); // <label id="code.input.rescale_data"/>
  }
  return result;
}
// END:arduino_communication

// START:drawing
void init_screen() {
  background(255); // <label id="code.input.clear_screen"/>
  stroke(0);
  strokeWeight(1);
  int[] radius_values = { 300, 250, 200, 150, 100, 50 };
  for (int r = 0; r < radius_values.length; r++) {
    final int current_radius = radius_values[r] * 2;
    ellipse(xCenter, yCenter, current_radius, current_radius);
  }
  strokeWeight(10);
}

void draw() {
  init_screen();
  int x = (int)(radius * Math.cos(degree * Math.PI / 180));
  int y = (int)(radius * Math.sin(degree * Math.PI / 180));  
  point(xCenter + x, yCenter + y);
  if (++degree == 360)
    degree = 0;
}
// END:drawing

