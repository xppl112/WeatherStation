#include <Arduino.h>
#include "StringUtils.h"

char* StringUtils::floatToString(float number, int widthBeforeDot, int widthAfterDot){
  char* str = new char[widthBeforeDot + 1 + widthAfterDot];
  dtostrf(number, widthAfterDot, widthAfterDot, str);
  return str;
}