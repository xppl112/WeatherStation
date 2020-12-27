#include <Arduino.h>
#include "LCD.h"

LCD::LCD(uint8_t i2c_address, uint8_t cols, uint8_t rows)
{
    _lcd = new LiquidCrystal_I2C(i2c_address, cols, rows);
    _i2c_address = i2c_address;    
    isConnected = false;
}

bool LCD::connect(bool waitUntilConnected){
    _lcd->init();
    isConnected = true;
    return true;
}

void LCD::backlight(bool enable){
    if(enable)_lcd->backlight();
    else _lcd->noBacklight();
}

void LCD::autoscroll(bool enable){
    if(enable)_lcd->autoscroll();
    else _lcd->noAutoscroll();
}

void LCD::setCursor(uint8_t col, uint8_t row){
    _lcd->setCursor(col, row);
}

void LCD::print(const char str[])
{
  _lcd->print(str);
}

void LCD::print(String str)
{
  _lcd->print(str);
}