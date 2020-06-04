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

#include "clsPCA9555.h"
#include "i2c_keypad.h"
#include "stepper.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
//#define LED_ONE 13
//#define LED_TWO ED8

void setup() {
  Serial.begin(9600);
  ioport.begin();
  ioport.setClock(400000);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  setup_keypad();
  setup_stepper();
}

// int previousDir = forward;

void loop() {
  unsigned long start = millis();
  Serial.println("test");
  switch (I2c_getKey(true)) {
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
    lcd.setCursor(0, 0);
    lcd.print("cancel settings");
    while (I2c_getKey(true) == 13) {
    }
    lcd.setCursor(0, 0);
    lcd.print("               ");
    break;
  case 15:
    lcd.setCursor(0, 0);
    lcd.print("confirm settings");
    while (I2c_getKey(true) == 15) {
    }
    lcd.setCursor(0, 0);
    lcd.print("                 ");
    break;
  case 16:
    while (I2c_getKey(true) == 16) {
      step(backward, fastStepDelay);
    }
    break;
  }
  lastRow = 99;
}
