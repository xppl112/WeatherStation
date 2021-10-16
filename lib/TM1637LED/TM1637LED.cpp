#include "TM1637LED.h"

TM1637LED::TM1637LED(uint8_t clkPin, uint8_t dioPin){
    _clkPin = clkPin;
    _dioPin = dioPin;
}

bool TM1637LED::connect(){
    _display = new TM1637(_clkPin, _dioPin);
    _display->begin();
    _display->setBrightness(5);
    clear();
    isConnected = true;
    return isConnected;
}

void TM1637LED::clear(){
    _display->clearScreen();
}

void TM1637LED::print(String str){
    clear();
    _display->display(str);
}

void TM1637LED::print(float number){
    clear();
    _display->display(number);
}

void TM1637LED::printDecimalWithUnit(float number, char unit){
    auto str = String(number);
    if(number < 0) str = str.substring(0, 3);
    else if(number >= 0 && number < 10) str = str.substring(0, 2);
    else str = str.substring(0, 3);
    str +=unit;  
    if(str.length() == 2)str = "  "+str;  
    else if(str.length() == 3)str = " "+str;  

    _display->display(str);
}

void TM1637LED::toggleColon(){
    isColonShowed = !isColonShowed;
    if(isColonShowed)_display->colonOn();
    else _display->colonOff();
}