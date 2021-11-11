#include <stdint.h>

const int PWMRANGE = 255;

class RGBLed
{
public:
  RGBLed(uint8_t pinR, uint8_t pinG, uint8_t pinB, bool commonAnode = true);
  void setColor(uint8_t R, uint8_t G, uint8_t B);
  void setBrightess(uint8_t brightnessPercent);

private:
  uint8_t _pinR; 
  uint8_t _pinG; 
  uint8_t _pinB;
  bool _commonAnode;
  uint8_t _brightnessPercent = 100;
};