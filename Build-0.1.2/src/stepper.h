
#define forward true
#define backward false
#define fast true
#define slow false

const int stepPin = 3;         // step pin on pin 3
const int dirPin = 4;          // direction pin on pin 4
const int farStop = 5;         // far stop input on pin 5
const int closeStop = 6;       // close stop input on pin 6
const int fastStepDelay = 100; // delay between step while moving fast
const int stepDelay = 1000;    // delay between steps while moving slow

void setup_stepper() {
  pinMode(farStop, INPUT_PULLUP);
  pinMode(closeStop, INPUT_PULLUP);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void stepForward(bool speed) {
  int del;
  digitalWrite(dirPin, forward); // Enables the motor to move forward
  delayMicroseconds(10);         // let output stabilise
  if (speed == fast) {
    del = fastStepDelay;
  } else {
    del = stepDelay;
  }
  // if (not digitalRead(farStop)) {
  digitalWrite(stepPin, HIGH);
  Serial.print("pin high forward  ");
  Serial.println(del);
  delayMicroseconds(del);
  digitalWrite(stepPin, LOW);
  Serial.print("pin low forward  ");
  Serial.println(del);
  Serial.println(" ");
  delayMicroseconds(del);
  //  }
}

void stepBackward(bool speed) {
  int del;
  digitalWrite(dirPin, backward); // Enables the motor to move forward
  delayMicroseconds(10);          // let output stabilise
  if (speed == fast) {
    del = fastStepDelay;
  } else {
    del = stepDelay;
  }
  // if (not digitalRead(closeStop)) {
  digitalWrite(stepPin, HIGH);
  Serial.print("pin high backward  ");
  Serial.println(del);
  delayMicroseconds(del);
  digitalWrite(stepPin, LOW);
  Serial.print("pin low backward  ");
  Serial.println(del);
  Serial.println(" ");
  delayMicroseconds(del);
  //  }
}
void homeFixture() {}
