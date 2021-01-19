#include <Arduino.h>
#include <Adafruit_SSD1306.h> 
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSerifBold24pt7b.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include "OLED.h"

OLED::OLED(uint8_t i2c_address, uint8_t width, uint8_t height)
{
    _i2c_address = i2c_address;
    _width = width;
    _height = height;

    _oled = new Adafruit_SSD1306(width, height);
}

bool OLED::connect(bool waitUntilConnected){
    isConnected = _oled->begin(SSD1306_SWITCHCAPVCC, _i2c_address);
    _oled->ssd1306_command(SSD1306_DISPLAYOFF);
    _oled->ssd1306_command(SSD1306_DISPLAYON);
    return isConnected;
}

void OLED::clear()
{
    _oled->clearDisplay();
}

void OLED::setWordWrapMode(bool wrap)
{
    _oled->setTextWrap(wrap);
}

void OLED::setCursor(uint8_t x, uint8_t y){
    _oled->setCursor(x, y);
}

void OLED::print(const char str[], OLEDFont font)
{   
    _oled->setTextColor(SSD1306_WHITE);

    if(font == FONT_TITLE){
        _oled->setFont(&FreeSerif9pt7b);
        _oled->setTextSize(1);
    }
    else if(font == FONT_BODY_BIG){
        _oled->setFont(&FreeSerifBold24pt7b);
        _oled->setTextSize(1);
    }
    else if(font == FONT_MEDIUM){
        _oled->setFont(&FreeSerifBold18pt7b);
        _oled->setTextSize(1);
    }
    else if(font == FONT_SMALL){
        _oled->setFont(&FreeSerifBold9pt7b);
        _oled->setTextSize(1);
    }

    _oled->print(str);
}

void OLED::print(String str, OLEDFont font)
{
    print(str.c_str(), font);
}

void OLED::render()
{
    _oled->display();
}