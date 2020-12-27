#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCD
{
public:
  LCD(uint8_t i2c_address, uint8_t cols = 16, uint8_t rows = 2);

  bool connect(bool waitUntilConnected = false);
  void backlight(bool enable);
  void autoscroll(bool enable);
  void setCursor(uint8_t col = 0, uint8_t row = 0);
  void print(const char str[]);
  void print(String str);

  bool isConnected;

private:
  LiquidCrystal_I2C* _lcd;
  uint8_t _i2c_address;
};