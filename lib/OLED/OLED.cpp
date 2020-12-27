#include <Arduino.h>
#include <ss_oled.h>
#include "OLED.h"

OLED::OLED(uint8_t i2c_address, uint8_t width, uint8_t height)
{
    _i2c_address = i2c_address;
    _width = width;
    _height = height;

    _oled = new SSOLED ();
}

bool OLED::connect(bool waitUntilConnected){
    int result = oledInit(_oled, OLED_128x64, _i2c_address, 0, 0, 1, -1, -1, -1, 400000L);
    isConnected = result != OLED_NOT_FOUND;
    return isConnected;
}

void OLED::clear(bool render)
{
    oledFill(_oled, 0, render);
}

void OLED::setWordWrapMode(bool wrap)
{
    oledSetTextWrap(_oled, wrap);
}

void OLED::setCursor(uint8_t x, uint8_t y){
    oledSetCursor(_oled, x, y);
}

void OLED::print(const char str[], bool render)
{        
    oledWriteString(_oled, -1, -1, -1, (char*)str, FONT_NORMAL, 0, render);
}

void OLED::print(String str, bool render)
{
    oledWriteString(_oled, 0, -1, -1, (char*)str.c_str(), FONT_NORMAL, 0, render);
}

void OLED::render()
{
    
}