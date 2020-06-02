/* this program is going to be moving the automated macro fixture
   It uses the DFRobot dfr0013 expansion board, which is driven by the
   clsPCA9555 driver. None time critical parts will be attached to the
   expansion board:
     LCD - screen driven by LiquidCrystal_I2C.h
     keypad - driven by I2c_getKey() and I2c_getCharachter() written by BvB
     also things like LED's will be driven by expansion board

   Arduino board:
     Stepper driver
     limit switches
     opto coupler for camera release
   let's see if we can use both ATOM and arduino IDE
   looks like we can
*/

#include "../lib/clsPCA9555.h"
#include "i2c_keypad.h"
#include "stepper.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//#define LED_ONE 13
//#define LED_TWO ED8

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
  Serial.begin(115200);
  // pinMode(LED_ONE, OUTPUT);
  // ioport.pinMode(LED_TWO, OUTPUT);
}

// int previousDir = forward;

void loop() {
  lcd.setCursor(6, 0);

  lcd.print(stepDelay);
  lcd.print("           ");
  lcd.setCursor(6, 1);
  // fastStepDelay = map(analogRead(highspeed_in), 0, 1023, 0, 255);
  // fastStepDelay = analogRead(highspeed_in);
  lcd.print(fastStepDelay);
  lcd.print("           ");
  Serial.println(digitalRead(farStop));
  unsigned long start = millis();

  switch (I2c_getKey(false)) {
  case 4:
    while (I2c_getKey(true) == 4) {
      step(forward, fastStepDelay);
    }
    break;
  case 8:
    while (I2c_getKey(true) == 8) {
      step(forward, stepDelay);
    }
    break;
  case 12:
    while (I2c_getKey(true) == 12) {
      step(backward, stepDelay);
    }
    break;
  case 13:
    Serial.println("reset setting");
    break;
  case 15:
    Serial.println("confirm setting");
    break;
  case 16:
    while (I2c_getKey(true) == 16) {
      step(backward, fastStepDelay);
    }
    break;
  }
  lastRow = 99;
}