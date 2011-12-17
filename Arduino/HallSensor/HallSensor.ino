/*
 *    FILE: MM01
 *  AUTHOR: Rob van den Tillaart
 *    DATE: 2010 03 19 
 *     URL: http://www.arduino.cc/playground/Code/HallEffect
 *
 * PURPOSE: use a A1301 as magnetometer   
 *
 * Pinlayout A1301
 * ==================
 *  1     GND
 *  2     signal    connected to Analog 0    
 *  3     Vdd +5V
 *
 */

int  time = 0;
int  oldtime = -1;
int  rawMM = 0;

#define BNULL 505L    // My midpoint, calibrate this
#define BFAC  1000L   // 2500 mv == 1000 Gauss in 505 steps

void setup() 
{
  // setup serial - diagnostics - port
  Serial.begin(9600);
}

void DoMeasurement()
{
  // measure magnetics
  rawMM = analogRead(0);   // Range : 0..1024

  Serial.print("MM: ");
  Serial.print(rawMM);

  long B = rawMM - BNULL;  // adjust midpoint 
  B = B * BFAC / BNULL;    // adjust scale -> -1000 .. +1000 Gauss

  Serial.print("  = B in Gauss: ");
  Serial.print(B);

  if (B > 0) Serial.println(" South-pole");
  else if (B <0) Serial.println(" North-pole");
  else Serial.println();
}

void loop() 
{
  time = millis()/1000;
  if (time == oldtime) 
  {
    delay(100);
  }
  else
  {
    oldtime = time;
    DoMeasurement();
  }
}
