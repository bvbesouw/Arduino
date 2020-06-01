
#define forward true
#define backward false
#define fast true
#define slow false

const int stepPin = 3;   // step pin on pin 3
const int dirPin = 4;    // direction pin on pin 4
const int farStop = 5;   // far stop input on pin 5
const int closeStop = 6; // close stop input on pin 6

unsigned int fastStepDelay;
unsigned int stepDelay;
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
    ++totalStepCounter;
  }
  totalStepCounter = 0;
}

void setup_stepper() {
  pinMode(farStop, INPUT_PULLUP);
  pinMode(closeStop, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, forward);
  // homeFixture();
}

void step(bool direction, byte speed) {

  if (direction != previousDir) {
    digitalWrite(dirPin, direction);
    previousDir = direction;
  }

  if ((direction == forward) and (not digitalRead(farStop))) {
    digitalWrite(stepPin, HIGH);
    ++totalStepCounter;
  }

  if ((direction == backward) and (not digitalRead(closeStop))) {
    digitalWrite(stepPin, HIGH);
    --totalStepCounter;
  }

  delayMicroseconds(speed);
  digitalWrite(stepPin, LOW);
  //  Serial.println(totalStepCounter);
}
