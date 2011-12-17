/*
 http://www.mindkits.co.nz/tutorials/arduino_tutorials/Tutorial-2

 Example 2.2 - our first LCD sketch
 Created 14/04/2010 ---  By John Boxall --- http://tronixstuff.wordpress.com ---  CC by-sa v3.0
 Just send some data to the LCD to experiment with it
*/
#include <LiquidCrystal.h> // we need this library for the LCD commands
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
float noisy = 0;
void setup()
{
  lcd.begin(16, 2);             // need to specify how many columns and rows are in the LCD unit
  lcd.println("tronixstuff!    ");
  lcd.setCursor(0,1);
  delay(2000);
  lcd.clear();
  randomSeed(analogRead(0)); // reseed the random number generator with some noise
}
void loop()
{
  noisy=random(1000);
  lcd.setCursor(0,0);
  lcd.print("Random Numbers!");
  lcd.setCursor(0,1);
  lcd.print("Number: ");
  lcd.print(noisy,0);
  delay(1000);
}
