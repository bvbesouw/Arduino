/* this program is going to be moving the automated macro fixture
 * It uses the DFRobot dfr0013 expansion board, which is driven by the
 * clsPCA9555 driver. None time critical parts will be attached to the
 * expansion board:
 *   LCD - screen driven by LiquidCrystal_I2C.h
 *   keypad - driven by I2c_getKey() and I2c_getCharachter() written by BvB
 *   also things like LED's will be driven by expansion board
 *
 * Arduino board:
 *   Stepper driver
 *   limit switches
 *   opto coupler for camera release
 * test
 */

#include "clsPCA9555.h"
#include "i2c_keypad.h"
#include "stepper.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C
    lcd(0x27, 16,
        2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define LED_ONE 13
#define LED_TWO ED8
#define lowspeed_in A0
#define highspeed_in A1

void setup() {
  ioport.begin();
  ioport.setClock(400000);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  setup_keypad();
  setup_stepper();

  lcd.setCursor(0, 0);
  lcd.print("low      ");
  lcd.setCursor(0, 1);
  lcd.print("high      ");
  Serial.begin(9600);
  pinMode(LED_ONE, OUTPUT);
  ioport.pinMode(LED_TWO, OUTPUT);
}

// int previousDir = forward;

void loop() {
  lcd.setCursor(6, 0);
  stepDelay = map(analogRead(lowspeed_in), 0, 1023, 1, 255);
  lcd.print(stepDelay);
  lcd.print("           ");
  lcd.setCursor(6, 1);
  fastStepDelay = map(analogRead(highspeed_in), 0, 1023, 1, 255);
  lcd.print(fastStepDelay);
  lcd.print("           ");

  unsigned long start = millis();
  // int charachter = I2c_getKey();

  switch (I2c_getKey()) {
  case 4:
    step(forward, fastStepDelay);
    break;
  case 8:
    step(forward, stepDelay);
    break;
  case 12:
    step(backward, stepDelay);
    break;
  case 16:
    step(backward, fastStepDelay);
    break;
  }

  unsigned long stop = millis();
  Serial.println(1000 / (stop - start));
}
