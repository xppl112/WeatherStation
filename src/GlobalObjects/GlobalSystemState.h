#ifndef GLOBALSYSTEMSTATE_H
#define GLOBALSYSTEMSTATE_H

#include <Arduino.h>
#include "Models/SystemErrorCodes.h"

class GlobalSystemState {    
public:
    GlobalSystemState(){
        _errors.reserve(10);
    }

    enum class PowerStatus {Regular, Reserve, Warning};
    enum class SystemStatus {Idle, Measuring, DataTransfer, SystemWarning, FatalFailure};

    struct SystemError {
        SystemErrorSeverity severity;
        SystemErrorCode errorCode;
        String description;
    };

    volatile PowerStatus powerStatus = PowerStatus::Regular;
    volatile SystemStatus systemStatus = SystemStatus::Idle;

    unsigned long getCurrentTimestamp(){
        if(_timeStampSnapshot == 0) return 0;
        unsigned long millisDiff = millis() - _millisSnaphot;
        return _timeStampSnapshot + millisDiff;
    }

    void updateTime(unsigned long currentTimestamp){
        _timeStampSnapshot = currentTimestamp;
        _millisSnaphot = millis();
    }

    void setSystemStatus(SystemStatus status){
        if(getErrorsCount() == 0){
            systemStatus = status;
        }
    }

    void setPowerStatus(PowerStatus status){
        if(getErrorsCount() == 0){
            powerStatus = status;
        }
    }

    void addError(SystemErrorCode code, SystemErrorSeverity severity = SystemErrorSeverity::SystemError, String description = ""){
        SystemError error {
            .severity = severity,
            .errorCode = code,
            .description = description
        };
        _errors.push_back(error);
    }

    int getErrorsCount(){ return _errors.size(); }
    std::vector<SystemError> getAllErrors() { return _errors; }
    void removeError(SystemErrorCode code){
        
    }
    void clearAllErrors(){ _errors.clear(); }

private:
    unsigned long _timeStampSnapshot = 0;
    unsigned long _millisSnaphot;

    std::vector<SystemError> _errors;
};
#endif