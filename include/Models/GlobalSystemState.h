#ifndef GLOBALSYSTEMSTATE_H
#define GLOBALSYSTEMSTATE_H

#include <Arduino.h>

class GlobalSystemState {    
public:
    unsigned long getCurrentTimestamp(){
        if(_timeStampSnapshot == 0) return 0;
        unsigned long millisDiff = millis() - _millisSnaphot;
        return _timeStampSnapshot + millisDiff;
    }

    void updateTime(unsigned long currentTimestamp){
        _timeStampSnapshot = currentTimestamp;
        _millisSnaphot = millis();
    }

private:
    unsigned long _timeStampSnapshot = 0;
    unsigned long _millisSnaphot;

};

#endif