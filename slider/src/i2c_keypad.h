#include "clsPCA9555.h"

PCA9555 ioport(0x20); // set I2c board address
#define R1 ED0 // Row 1 on pin 0 , using ED to clarify it is on expansion board
#define R2 ED1 // Row 2 on pin 1
#define R3 ED2 // Row 3 on pin 2
#define R4 ED3 // Row 4 on pin 3
#define C1 ED4 // Column 1 on pin 4
#define C2 ED5 // Column 2 on pin 5
#define C3 ED6 // Column 3 on pin 6
#define C4 ED7 // Column 4 on pin 7

void setup_keypad() {
  ioport.pinMode(R1, INPUT_PULLUP); // Row 1 is an input
  ioport.pinMode(R2, INPUT_PULLUP); // Row 2 is an input
  ioport.pinMode(R3, INPUT_PULLUP); // Row 3 is an input
  ioport.pinMode(R4, INPUT_PULLUP); // Row 4 is an input
  ioport.pinMode(C1, OUTPUT);       // Column 1 is an output
  ioport.digitalWrite(C1, LOW);     // Set output LOW
  ioport.pinMode(C2, OUTPUT);       // Column 2 is an output
  ioport.digitalWrite(C2, LOW);     // Set output LOW
  ioport.pinMode(C3, OUTPUT);       // Column 3 is an output
  ioport.digitalWrite(C3, LOW);     // Set output LOW
  ioport.pinMode(C4, OUTPUT);       // Column 4 is an output
  ioport.digitalWrite(C4, LOW);     // Set output LOW
}

/*
   I2c_getKey returns the # of the key pressed, top left = 1 bottom right = 16
   returns 0 if no key is pressed
*/
int lastRow;
int key = 99;

int I2c_getKey(bool fast) { // when fast == true, then check of row has changed
                            // and return lastkey
  /*if (fast) {
    if (not ioport.digitalRead(lastRow)) {
      return key;
    }
  }
*/
  if (not ioport.digitalRead(lastRow)) {
    return key;
  }
  key = 0;                           // Reset return Value
  for (int i = R1; i <= R4; ++i) {   // Go through rows 0-3
    if (not ioport.digitalRead(i)) { // If a row is low go check the column
      int c = C1;                    // Start at Column 1
      while (not ioport.digitalRead(i))
        ioport.digitalWrite(c++, HIGH); // go to next column and set it HIGH
      int col = c;
      for (c = C1; c < col; ++c)     // go though all columns
        ioport.digitalWrite(c, LOW); // make them low again
      key = i * 4 + col - 4;
      lastRow = i;
    }
  }
  return key;
}

/*
   I2c_getCharachter returns the charachter of the key pressed as defined by the
   keys array below
*/

char keys[]{'1', '2', '3', 'A',  // Row 1 charachters
            '4', '5', '6', 'B',  // Row 2 charachters
            '7', '8', '9', 'C',  // Row 3 charachters
            '*', '0', '#', 'D'}; // Row 4 charachters
char I2c_getCharachter() {
  return keys[I2c_getKey(false) - 1]; // Return the charachter of the pushed key
}

/*
   500Pulse is true for 500ms every second, 500Impulse is high for 1 cycle every
   500ms
*/

bool pulseState,
    impulse500; // impulse_500 is high for 1 cycle every 500ms
unsigned long previous_millis;

bool pulse500() // is HIGH for 500ms every 1000ms
{
  unsigned long current_millis = millis();

  impulse500 = LOW; // impulse_500 is high for 1 cycle every 500ms
  if (current_millis - previous_millis > 500) {
    previous_millis = current_millis;
    pulseState = !pulseState;
    impulse500 = HIGH;
  }
  return pulseState;
}
