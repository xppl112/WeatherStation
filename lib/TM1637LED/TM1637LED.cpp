#include "TM1637LED.h"

TM1637LED::TM1637LED(uint8_t clkPin, uint8_t dioPin){
    _clkPin = clkPin;
    _dioPin = dioPin;
}

bool TM1637LED::connect(){
    _display = new TM1637(_clkPin, _dioPin);
    _display->begin();
    _display->setBrightness(8);
    clear();
    isConnected = true;
    return isConnected;
}

void TM1637LED::clear(){
    _display->clearScreen();
    _display->colonOff();
    _display->refresh();
}

void TM1637LED::print(String str){
    clear();
    _display->display(str);
}

void TM1637LED::print(float number){
    
    _display->display(number);
}

void TM1637LED::printDecimalWithUnit(float number, char unit){
    //clear();

    auto str = String((int)number)+"."+String(number*10 - (int)number*10);
    if(number < 0) str = str.substring(0, 4);
    else if(number >= 0 && number < 10) str = str.substring(0, 3);
    else str = str.substring(0, 4);
    str +=unit;  

    auto offset = 4 - (str.length()-1);
    _display->display(str, true, false, offset);
}

void TM1637LED::toggleColon(){
    isColonShowed = !isColonShowed;
    if(isColonShowed)_display->colonOn();
    else _display->colonOff();
}