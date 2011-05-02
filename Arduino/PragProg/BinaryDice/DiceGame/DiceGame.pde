#include <Bounce.h>

const unsigned int LED_BIT0 = 12;
const unsigned int LED_BIT1 = 11;
const unsigned int LED_BIT2 = 10;
const unsigned int START_BUTTON_PIN = 5;
const unsigned int GUESS_BUTTON_PIN = 7;
const unsigned int BAUD_RATE = 9600;

void setup() {
  pinMode(LED_BIT0, OUTPUT);
  pinMode(LED_BIT1, OUTPUT);
  pinMode(LED_BIT2, OUTPUT);  
  pinMode(START_BUTTON_PIN, INPUT);  
  pinMode(GUESS_BUTTON_PIN, INPUT);  
  randomSeed(analogRead(A0));
  Serial.begin(BAUD_RATE);
}

const unsigned int DEBOUNCE_DELAY = 20;
Bounce start_button(START_BUTTON_PIN, DEBOUNCE_DELAY); // <label id="code.binary_die.bounce_start"/>
Bounce guess_button(GUESS_BUTTON_PIN, DEBOUNCE_DELAY); // <label id="code.binary_die.bounce_guess"/>
int guess = 0;

void loop() {
  handle_guess_button();
  handle_start_button();
}

void handle_guess_button() {
  if (guess_button.update()) {
    if (guess_button.read() == HIGH) {
      guess = (guess % 6) + 1; // <label id="code.binary_die.range_check"/>
      output_result(guess);
      Serial.print("Guess: ");
      Serial.println(guess);
    }
  }
}

void handle_start_button() {
  if (start_button.update()) {
    if (start_button.read() == HIGH) {
      const int result = random(1, 7);
      output_result(result);
      Serial.print("Result: ");
      Serial.println(result);
      if (guess > 0) {
        if (result == guess) {
          Serial.println("You win!");
          hooray();
        } else {
          Serial.println("You lose!");
        }
      }
      delay(2000);
      guess = 0;
    }
  }
}

void output_result(const long result) {
  digitalWrite(LED_BIT0, result & B001);
  digitalWrite(LED_BIT1, result & B010);
  digitalWrite(LED_BIT2, result & B100);
}

void hooray() {
  for (int i = 0; i < 3; i++) {
    output_result(7);
    delay(500);
    output_result(0);
    delay(500);
  }
}

