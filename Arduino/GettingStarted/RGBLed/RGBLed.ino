#define RED     9  // RED pin of the LED to PWM pin 37 
#define GREEN  10  // GREEN pin of the LED to PWM pin 36
#define BLUE   11  // BLUE pin of the LED to PWM pin 35
#define STEP   30  // step increment value
#define POT    1   // potentio meter
#define BUTTON 4   // stepper button

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

//    r = (constrain(color, 0, 255));   //red
//    g = (constrain(color, 256, 511) - 256); //green
//    b = (constrain(color, 512, 767) - 512); //blue

  txt = String("C:");
  txt.concat(color);
  txt.concat(" R:");
  txt.concat(r);
  txt.concat(" G:");
  txt.concat(g);
  txt.concat(" B:");
  txt.concat(b);

  Serial.println(txt);
  
  analogWrite(RED,   r);
  analogWrite(GREEN, g);
  analogWrite(BLUE,  b);
}




//void loop() {
//  for(int     r = 0; r < 255; r+=STEP) {
//    for(int   g = 0; g < 255; g+=STEP) {
//      for(int b = 0; b < 255; b+=STEP) {
//        analogWrite(RED,   r);
//        analogWrite(GREEN, g);
//        analogWrite(BLUE,  b);
//        txt2 = txt + "R:" + r + " G:" + g + " B:"+ b;
//        Serial.println(txt2);
////        delay(10);
//      }
//    }
//  }
//}

