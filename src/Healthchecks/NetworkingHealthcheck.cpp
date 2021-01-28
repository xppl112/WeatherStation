#include "Healthchecks/NetworkingHealthcheck.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

NetworkingHealthcheck::NetworkingHealthcheck(){
}

HealthStatus NetworkingHealthcheck::check(){
    bool isNetworkErrorFound = false;
    for(auto error : globalSystemState->getAllErrors()){
        if(error.errorCode == SystemErrorCode::Network_BackendServerConnectionFailure || 
        error.errorCode == SystemErrorCode::Network_BackendServerInternalError || 
        error.errorCode == SystemErrorCode::Network_WifiConnectionFailure) isNetworkErrorFound = true;
    }

    return isNetworkErrorFound ? HealthStatus::HEALTH_WARNING : HealthStatus::HEALTH_OK;
}

void NetworkingHealthcheck::handleCheckStatus(HealthStatus healthStatus){
    // There is no way to restart onle Wifi module
}