/*
 exercise 2.1 - Climate Control Judge
 
 Created 14/04/2010 ---  By John Boxall --- http://tronixstuff.wordpress.com ---  CC by-sa v3.0 Share the love!
 
 Measures temperature with Analog Devices TMP36 and compares against minimum temperature to use a heater or air conditioner
 
 */
int redLED = 13; // define which colour LED is in which digital output
int greenLED = 12;
int blueLED = 11;
float voltage = 0; // set up some variables for temperature work
float sensor = 0;
float celsius = 0;
float heaterOn = 15; // it's ok to turn on the heater if the temperature is below this value
float airconOn = 26; // it's ok to turn on the air conditioner if the temperature is above this value
void setup()
{
  Serial.begin(9600);   // activate the serial output connection
  pinMode(redLED, OUTPUT);    // set the digital pins for LEDs to outputs
  pinMode(greenLED, OUTPUT);  // not necessary for analogue input pin
  pinMode(blueLED, OUTPUT);
}
void loop()
{
  digitalWrite(redLED, LOW);    // switch off the LEDs
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  // read the temperature sensor and convert the result to degrees Celsius
  sensor = analogRead(0);       // TMP36 sensor output pin is connected to Arduino analogue pin 0
  voltage = (sensor*5000)/1024; // convert raw sensor value to millivolts
  voltage = voltage-500;        // remove voltage offset
  celsius = voltage/10;         // convert millivolts to Celsius
  // now decide if it is too hot or cold.
  Serial.print("Temperature: ");
  Serial.print(celsius,2);
  Serial.println(" degrees C");
  
  if (celsius>=airconOn)
  {
    digitalWrite(blueLED, HIGH); // ok to turn on the air conditioner
  } 
  else if (celsius<=heaterOn)
  {
    digitalWrite(redLED, HIGH);
  } 
  else
  {
    digitalWrite(greenLED, HIGH); // everything normal
  }
  delay(1000); // necessary to hold reading, otherwise the sketch runs too quickly and doesn't give the LEDs enough time to
  // power up before shutting them down again

}


