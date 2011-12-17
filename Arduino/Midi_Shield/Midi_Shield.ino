// SparkFun MIDI Sheild and MIDI Breakout test code
// Defines bare-bones routines for sending and receiving MIDI data
// Written 02/16/10


// defines for MIDI Shield components only
#define KNOB1  0
#define KNOB2  1

#define BUTTON1  2
#define BUTTON2  3
#define BUTTON3  4

#define STAT1  7
#define STAT2  6

#define OFF 1
#define ON 2
#define WAIT 3

byte incomingByte;
byte note;
byte velocity;
int pot;

byte byte1;
byte byte2;
byte byte3;

byte channel = 0x90; // 1
byte middle_velocity = 0x45;

int action = 2; //1 =note off ; 2=note on ; 3= wait



void setup() {

  pinMode(STAT1,OUTPUT);   
  pinMode(STAT2,OUTPUT);

  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);

  digitalWrite(BUTTON1,HIGH);
  digitalWrite(BUTTON2,HIGH);
  digitalWrite(BUTTON3,HIGH);

  for(int i = 0;i < 10;i++) // flash MIDI Sheild LED's on startup
  {
    digitalWrite(STAT1,HIGH);  
    digitalWrite(STAT2,LOW);
    delay(30);
    digitalWrite(STAT1,LOW);  
    digitalWrite(STAT2,HIGH);
    delay(30);
  }
  digitalWrite(STAT1,HIGH);   
  digitalWrite(STAT2,HIGH);

  //start serial with midi baudrate 31250
  Serial.begin(31250);     
}

void loop () {

  //*************** MIDI OUT ***************//

  pot = analogRead(0);
  note = pot/8;  // convert value to value 0-127
  if(button(BUTTON1) || button(BUTTON2) || button(BUTTON3))
  {  
    Midi_Send(channel,note,middle_velocity);
    blink();
    while(button(BUTTON1) || button(BUTTON2) || button(BUTTON3));
  }

  //*************** MIDI LOOPBACK ******************//
  if(Serial.available() > 0)
  {
    byte1 = Serial.read();
    byte2 = Serial.read();
    byte3 = Serial.read();

    Midi_Send(byte1, byte2, byte3);
  }

  //*************** MIDI IN ***************//
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // wait for as status-byte, channel 1, note on or off
    if (incomingByte == int(channel)) // Note on
    { 
      action = OFF;
    }
    else if (incomingByte== int(0x80)) // Note off
    { 
      action = ON;
    }
    else if (note==0 && action != WAIT) // note on, wait for note value
    { 
      note=incomingByte;
    }
    else if (note!=0 && action != WAIT)  // velocity
    { 
      velocity = incomingByte;
      if(action == ON){ 
        Midi_Send(channel,note,velocity); 
      }
      if(action == OFF){ 
        Midi_Send((channel - 0x10),note,velocity); 
      }
      note=0;
      velocity=0;
      action=WAIT;
    }
    else{
    }
  }

}

void Midi_Send(byte cmd, byte data1, byte data2) {
  Serial.print(cmd);
  Serial.print(data1);
  Serial.print(data2);
}

void blink(){
  digitalWrite(STAT1, HIGH);
  delay(100);
  digitalWrite(STAT1, LOW);
  delay(100);
}

char button(char button_num)
{
  return (!(digitalRead(button_num)));
}

// http://www.tigoe.net/pcomp/code/communication/midi
// 
// Value (decimal)	Value (Hex)	Command	Data bytes
// 128-143	80-8F	Note off	2 (note, velocity)
// 144-159	90-9F	Note on	2 (note, velocity)
// 160-175	A0-AF	Key Pressure	2 (note, key pressure)
// 176-191	B0-BF	Control Change	2 (controller no., value)
// 192-207	C0-CF	Program Change	1 (program no.)
// 208-223	D0-DF	Channel Pressure	1 (pressure)
// 224-239	E0-EF	Pitch Bend	2 (least significant byte, most significant byte)
