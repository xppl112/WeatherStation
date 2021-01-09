#include "LCD.h"
#include "OLED.h"

LCD* lcd;
OLED* oled;

  oled = new OLED(0x3C);
  oled->connect();
  oled->clear(true);
 
  lcd = new LCD(0x27, 16, 2);
  lcd->connect();
  lcd->backlight(true);

    char* str = new char[16];
  
 
  
  lcd->setCursor();  
  char* measureString = floatToString(data.temperatureCelsium, 2);
  sprintf(str, "T:%s", measureString);
  lcd->print(str);
  delete measureString;
  delete str;
  
  str = new char[16];
  measureString = floatToString(data.humidityPercent, 2);
  lcd->setCursor(8, 0);
  sprintf(str, " H:%s", measureString);
  lcd->print(str);
  delete measureString;
  delete str;


  
  str = new char[16];
  sprintf(str, "RAM: %d   ", freeMemory());
  lcd->setCursor(0, 1);
  lcd->print(str);
  delete str;

  oled->setWordWrapMode(true);
  oled->clear(true);
  oled->setCursor(0,0);

  if (dConsole.length() > 0) { 
        oled->print(dConsole, true);
  } 