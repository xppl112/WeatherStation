#include <stdint.h>
#include <Time.h>

class DateTimeUtils
{
public:
  static String formatFromTimestamp(unsigned long timestamp, bool showDate = true, bool showTime = true);
  static int getHourFromTimestamp(unsigned long timestamp);

private:
  static tm* getLocalTime(unsigned long timestamp);
};