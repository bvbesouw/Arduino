#include "clsPCA9555.h"

#define forward true
#define backward false
#define fast true
#define slow false

const int stepPin = 3;     // step pin on pin 3
const int dirPin = 4;      // direction pin on pin 4
const int farStop = ED8;   // far stop input on expansion pin 8
const int closeStop = ED9; // close stop input on expansion pin 9

const byte fastStepDelay = 0;
const byte stepDelay = 5;

bool previousDir = forward;
unsigned long totalStepCounter;

void homeFixture() {
  while ((not digitalRead(closeStop))) { // move to back stop
    digitalWrite(dirPin, backward);
    digitalWrite(stepPin, HIGH);
    delay(20);
    digitalWrite(stepPin, LOW);
    totalStepCounter = 10; // make sure it won't go negative
  }

  while ((digitalRead(closeStop))) { // move to until away from closeStop
    digitalWrite(dirPin, forward);
    digitalWrite(stepPin, HIGH);
    delay(20);
    digitalWrite(stepPin, LOW);
  }
  totalStepCounter += 0;
}

void setup_stepper() {
  ioport.pinMode(farStop, INPUT_PULLUP);
  ioport.pinMode(closeStop, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, forward);
  // homeFixture();
}

void step(bool direction, unsigned int speed) {

  if (direction != previousDir) {
    digitalWrite(dirPin, direction);
    previousDir = direction;
  }

  if ((direction == forward) && (not ioport.digitalRead(farStop))) {
    digitalWrite(stepPin, HIGH);
    ++totalStepCounter;
  }

  if ((direction == backward) && (not digitalRead(closeStop))) {
    digitalWrite(stepPin, HIGH);
    --totalStepCounter;
  }

  delay(speed);
  digitalWrite(stepPin, LOW);
  // Serial.println(speed);
}
