// START:boilerplate
import processing.serial.*;

final float  MAX_WORKING_TEMP = 32.0;
final int    LINE_FEED = 10;
final int    BAUD_RATE = 9600;
final String CONSUMER_KEY = "<YOUR CONSUMER KEY>";
final String CONSUMER_SECRET = "<YOUR CONSUMER SECRET>";
final String ACCESS_TOKEN = "<YOUR ACCESS TOKEN>";
final String ACCESS_TOKEN_SECRET = "<YOUR ACCESS TOKEN SECRET>";

Serial arduinoPort;

void setup() {
  println(Serial.list());
  arduinoPort = new Serial(this, Serial.list()[0], BAUD_RATE);
  arduinoPort.bufferUntil(LINE_FEED);
}

void draw() {} 
// END:boilerplate

// START:main
void serialEvent(Serial port) {
  final String arduinoData = port.readStringUntil(LINE_FEED);

  if (arduinoData != null) {
    final String[] data = split(trim(arduinoData), ' ');
    if (data.length == 2 && 
        (data[1].equals("C") || data[1].equals("F")))
    {
      float temperature = float(data[0]);
      println(temperature);
      int sleepTime = 5 * 60 * 1000;
      if (temperature > MAX_WORKING_TEMP) {
        tweetAlarm();
        sleepTime = 120 * 60 * 1000;
      }
      try {
        Thread.sleep(sleepTime);
      }
      catch(InterruptedException ignoreMe) {}
    }
  }
}

void tweetAlarm() {
  TwitterFactory factory = new TwitterFactory();
  Twitter twitter = factory.getInstance();
  twitter.setOAuthConsumer(CONSUMER_KEY, CONSUMER_SECRET);
  AccessToken accessToken = new AccessToken(
    ACCESS_TOKEN, 
    ACCESS_TOKEN_SECRET
  );
  twitter.setOAuthAccessToken(accessToken);
  try {
    Status status = twitter.updateStatus(
      "Someone, please, take me to the beach!"
    );
    println(
      "Successfully updated status to '" + status.getText() + "'."
    );
  }
  catch (TwitterException e) {
    e.printStackTrace();
  }
}
// END:main

