#include <Arduino.h>

#define DIR_PIN 16
#define STEP_PIN 17
#define ENA_PIN 5

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);

  // Enable motor (active HIGH)
  digitalWrite(ENA_PIN, HIGH);

  // Small blink to confirm the board is alive
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
}

void loop() {
  // Forward rotation
  digitalWrite(DIR_PIN, HIGH);
  for (int i = 0; i < 800; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(800);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(800);
  }
  delay(500);

  // Reverse rotation
  digitalWrite(DIR_PIN, LOW);
  for (int i = 0; i < 800; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(800);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(800);
  }
  delay(500);
}
