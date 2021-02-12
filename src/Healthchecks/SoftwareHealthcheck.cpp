#include "Healthchecks/SoftwareHealthcheck.h"
#include "Config.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

SoftwareHealthcheck::SoftwareHealthcheck(){
}

HealthStatus SoftwareHealthcheck::check(){
    HealthStatus status = HealthStatus::HEALTH_OK;
    for(auto error : globalSystemState->getAllErrors()){
        // There is dedicated healtheck for network issues
        if(error.errorCode == SystemErrorCode::Network_BackendServerConnectionFailure || 
        error.errorCode == SystemErrorCode::Network_BackendServerInternalError || 
        error.errorCode == SystemErrorCode::Network_WifiConnectionFailure) continue;
            
        if(error.severity == SystemErrorSeverity::SystemWarning && status != HealthStatus::HEALTH_ERROR) status = HealthStatus::HEALTH_WARNING;
        else if(error.severity == SystemErrorSeverity::SystemError) status = HealthStatus::HEALTH_ERROR;
    }

    handleCheckStatus(status);
    return status;
}

void SoftwareHealthcheck::handleCheckStatus(HealthStatus healthStatus){    
    if(healthStatus == HealthStatus::HEALTH_ERROR){
        _healthErrorDetectionCount++;
        if(_healthErrorDetectionCount >= SOFTWARE_ERRORS_RESTART_LIMIT){
            ESP.restart();
        }
    }
    else _healthErrorDetectionCount = 0;
}