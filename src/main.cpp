#include "M5Core2.h"

void setup()
{
  M5.Lcd.setTextFont(FONT2);
  M5.begin();

  M5.Lcd.print("Hello World!");
}

void loop()
{
}