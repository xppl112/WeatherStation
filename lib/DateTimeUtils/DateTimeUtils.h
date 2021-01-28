#include <stdint.h>
#include <Time.h>

class DateTimeUtils
{
public:
  static String formatFromTimestamp(unsigned long timestamp, bool date = true, bool time = true);
  static int getHourFromTimestamp(unsigned long timestamp);

private:
  static tm* getLocalTime(unsigned long timestamp);
};