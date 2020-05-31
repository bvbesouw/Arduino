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
#include <LiquidCrystal_I2C.h>
//#include "BvB-Functions.h"   //contains keypad functions, 1/2 second pulse
#include "i2c_keypad.h"
#include "stepper.h"

LiquidCrystal_I2C
    lcd(0x27, 16,
        2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define LED_ONE 13
#define LED_TWO ED8
#define analog_in A0;

void setup() {
  ioport.begin();
  ioport.setClock(400000);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  setup_keypad();
  setup_stepper();

  Serial.begin(9600);
  pinMode(LED_ONE, OUTPUT);
  ioport.pinMode(LED_TWO, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Press a Key");
}

int previousKey = 0, Charachter;

void loop() {

  // use step as

  // stepForward(fast);
  digitalWrite(LED_ONE, pulse500());
  ioport.digitalWrite(LED_TWO, !pulse500());

  // unsigned long start = millis();
  Charachter = I2c_getKey(); // Get key from keypad on extension board
  if (Charachter == 4) {
    stepForward(fast);
    // lcd.setCursor(0, 0);
    // lcd.print("fast forward");
  }
  if (Charachter == 8) {
    stepForward(slow);
    // lcd.setCursor(0, 0);
    // lcd.print("slow forward");
  }
  if (Charachter == 16) {
    stepBackward(fast);
    // lcd.setCursor(0, 0);
    // lcd.print("fast forward");
  }
  if (Charachter == 12) {
    stepBackward(slow);
    // lcd.setCursor(0, 0);
    // lcd.print("slow forward");
  }

  lcd.setCursor(0, 0);
  lcd.print("        ");
  // int stop = millis() - start;
  /*
    lcd.setCursor(0, 0);
    lcd.print(stop);
    lcd.print("          ");

    if (Charachter != previousKey) { // only output when there is a new
    charachter previousKey = Charachter; if (Charachter != 0) { lcd.setCursor(0,
    1); lcd.print(I2c_getCharachter()); } else { lcd.setCursor(0, 1);
        lcd.print("  ");
      }
    }
          */
}
