
#define forward true
#define backward false
#define fast true
#define slow false

const int stepPin = 3;   // step pin on pin 3
const int dirPin = 4;    // direction pin on pin 4
const int farStop = 5;   // far stop input on pin 5
const int closeStop = 6; // close stop input on pin 6
// const int fastStepDelay = 10; // delay between step while moving fast
// const int stepDelay = 100;    // delay between steps while moving slow
unsigned int fastStepDelay;
unsigned int stepDelay;

void setup_stepper() {
  pinMode(farStop, INPUT_PULLUP);
  pinMode(closeStop, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void step(bool direction, bool speed) {
  unsigned int del;
  if (speed == fast) {
    del = fastStepDelay;
  } else {
    del = stepDelay;
  }
  // Serial.println(del);
  digitalWrite(dirPin, direction); // Enables the motor to move forward
  delayMicroseconds(10);           // let output stabilise

  if ((direction == forward) and (not digitalRead(farStop))) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(50); // pulse for 100 microseconds
    digitalWrite(stepPin, LOW);
    delay(del); // wait for delay
  }

  if ((direction == backward) and (not digitalRead(closeStop))) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(50); // pulse for 100 microseconds
    digitalWrite(stepPin, LOW);
    delay(del); // wait for delay
  }
}

void homeFixture() {}
