#include <Arduino.h>
#include "DateTimeUtils.h"

String DateTimeUtils::formatFromTimestamp(unsigned long timestamp, bool showDate, bool showTime){
    tm* t = getLocalTime(timestamp);

    char str[30];
    sprintf(str, "%02d.%02d.%04d %02d:%02d", t->tm_mday, t->tm_mon, t->tm_year, t->tm_hour, t->tm_min);
    delete(t);

    return String(str);
}

int DateTimeUtils::getHourFromTimestamp(unsigned long timestamp){
    tm* time = getLocalTime(timestamp);
    int hour = time->tm_hour;
    delete(time);
    
    return hour;
}

tm* DateTimeUtils::getLocalTime(unsigned long timestamp){
    time_t rawTime = timestamp;
    return localtime(&rawTime);
}