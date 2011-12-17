/*

Philips Mood light

RED    ---|>|---/\/\/--+
GREEN  ---|>|---/\/\/--+
BLUE   ---|>|---/\/\/--+
                       |
GND    ----------+-----+
                 +
+5v    ---/\/\/--+
POT    ----^

*/

#define RED     9  // RED pin of the LED to PWM pin 37 
#define GREEN  10  // GREEN pin of the LED to PWM pin 36
#define BLUE   11  // BLUE pin of the LED to PWM pin 35
#define POT    1   // potentio meter
#define BUTTON 4   // stepper button

#define STEP   30  // step increment value

int brightness = 0; // will be incresed with stepper button 
int color      = 0; // color of led

String txt;

void setup()
{
  pinMode(BUTTON, INPUT); 
  pinMode(POT,    INPUT); 

  pinMode(RED,    OUTPUT); 
  pinMode(GREEN,  OUTPUT); 
  pinMode(BLUE,   OUTPUT); 

  Serial.begin(9600);

  txt = String("");
}

void loop() {
  color = analogRead(POT);
  setColor(color);
  delay(50);
}

void setColor(int color) {
  int r, g, b;

  if (color < 255) {
    r = color;
    g = 0;
    b = 255 - color;
  } else if (color < 512) {
    r = 512 - color;
    g = color - 255;
    b = 0;
  } else if (color < 768) {
    r = 0;
    g = 768 - color;
    b = color - 512;
  } else {
    r = color - 768;
    g = 0;
    b = 1024 - color;
  } 

  analogWrite(RED,   r);
  analogWrite(GREEN, g);
  analogWrite(BLUE,  b);

  Serial.print("C:");
  Serial.print(color);
  Serial.print("\tR:");
  Serial.print(r);
  Serial.print("\tG:");
  Serial.print(g);
  Serial.print("\tB:");
  Serial.print(b);
  Serial.println("");
  
}

