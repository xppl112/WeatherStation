#ifndef GLOBALSYSTEMSTATE_H
#define GLOBALSYSTEMSTATE_H

#include <Arduino.h>

class GlobalSystemState {    
public:
    GlobalSystemState(){
    }

    volatile bool isNightMode = false;
    volatile uint8_t unsyncronizedWeatherReports = 0;

    unsigned long getCurrentTimestamp(){
        if(_timeStampSnapshot == 0) return 0;
        unsigned long millisDiff = millis() - _millisSnaphot;
        return _timeStampSnapshot + (millisDiff / 1000);
    }

    void updateTime(unsigned long currentTimestamp){
        _timeStampSnapshot = currentTimestamp;
        _millisSnaphot = millis();
    }

    void setNightMode(bool nightMode){
        isNightMode = nightMode; 
    }

private:
    unsigned long _timeStampSnapshot = 0;
    unsigned long _millisSnaphot;
};
#endif