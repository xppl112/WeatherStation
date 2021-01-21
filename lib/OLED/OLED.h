#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <stdint.h>
#include <Adafruit_SSD1306.h> 

enum OLEDFont {FONT_TITLE, FONT_BODY_BIG, FONT_MEDIUM, FONT_SMALL, FONT_SMALL_THIN};

class OLED
{
public:
  OLED(uint8_t i2c_address, uint8_t width = 128, uint8_t hight = 64);

  bool connect(bool waitUntilConnected = false);
  void clear();
  void setWordWrapMode(bool wrap);
  void setCursor(uint8_t x, uint8_t y);
  void print(const char str[], OLEDFont font = FONT_SMALL);
  void print(String str, OLEDFont font = FONT_SMALL);
  void render();

  bool isConnected;

private:
  Adafruit_SSD1306* _oled;
  uint8_t _i2c_address;
  uint8_t _width;
  uint8_t _height;
};

#endif