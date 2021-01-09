#include <stdint.h>

class StringUtils
{
public:
  static char* floatToString(float number, int widthBeforeDot, int widthAfterDot = 2);
};