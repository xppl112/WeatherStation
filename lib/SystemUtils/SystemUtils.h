#include <stdint.h>

class SystemUtils
{
public:
  static void printAllI2C();
  static bool isI2CDeviceConnected(uint8_t address);
  static int getFreeMemory();
};