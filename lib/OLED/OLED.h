#include <Arduino.h>
#include <stdint.h>
#include <ss_oled.h>

class OLED
{
public:
  OLED(uint8_t i2c_address, uint8_t width = 128, uint8_t hight = 64);

  bool connect(bool waitUntilConnected = false);
  void clear(bool render = false);
  void setWordWrapMode(bool wrap);
  void setCursor(uint8_t x, uint8_t y);
  void print(const char str[], bool render = false);
  void print(String str, bool render = false);
  void render();

  bool isConnected;

private:
  SSOLED* _oled;
  uint8_t _i2c_address;
  uint8_t _width;
  uint8_t _height;
};