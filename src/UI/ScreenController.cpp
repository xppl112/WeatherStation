#include "UI/ScreenController.h"
#include "config.h"

ScreenController::ScreenController(){
    _oled = new OLED(OLED_I2C_ADDR);
}

void ScreenController::resetScreen(){
    _oled->connect();
    _oled->clear(true);
}

void ScreenController::showWeather(){
    _oled->setWordWrapMode(true);
    _oled->clear(true);
    _oled->setCursor(0,0);

    _oled->print("test", true);
}


 

 /*
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

*/