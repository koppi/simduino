#ifdef SIM
#include "Sim.h"
#endif

#include <LiquidCrystal.h>

LCD lcd;

void setup() {
  Serial.begin(9600);

  lcd.begin(16,2);  // initialize the lcd 

  Serial.write("Hello, World!\n");
  lcd.print("Hello, World!");

  lcd.setCursor(0,1);
  lcd.print("Line2!");
}

void loop() {
  for (int p = 0; p < 13; p++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

  for (int p = 0; p < 29; p++) {
    lcd.scrollDisplayRight();
    delay(150);
  }

  for (int p = 0; p < 16; p++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

  delay(1000);
}

