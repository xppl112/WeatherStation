#include "Integrations/BackendClient.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

BackendClient::BackendClient(BackendClientConfig config){
    _config = config;
    _esp = new EspWifiClient();
}

int BackendClient::GetServerTime(){
    if(connectWifi()){
        HttpResponse response = _esp->sendGetRequest(
            _config.ServerHost, 
            _config.ServerApiGetTimeUrl);
        disconnectWifi();

        if(!response.success){
            globalSystemState->addError(
                SystemErrorCode::Network_BackendServerConnectionFailure, 
                SystemErrorSeverity::SystemWarning, 
                "Endpoint '"+ String(_config.ServerApiGetTimeUrl) +"' connection failed");
        }
        else globalSystemState->removeError(SystemErrorCode::Network_BackendServerConnectionFailure);

        if(response.statusCode != 200){
            globalSystemState->addError(
                SystemErrorCode::Network_BackendServerInternalError, 
                SystemErrorSeverity::SystemWarning, 
                "Endpoint '"+ String(_config.ServerApiGetTimeUrl) +"' responded " + String(response.statusCode));
        }
        else {
            globalSystemState->removeError(SystemErrorCode::Network_BackendServerInternalError);
            return atoi(response.payload.c_str());
        }
    }

    return -1;
}

bool BackendClient::SendWeatherData(std::queue<WeatherMonitorData>* weatherDataCollection) {
    if(weatherDataCollection->size() == 0) return true;

    if(connectWifi()){
        for(int batchNum = 0; batchNum < _config.BatchRequestsMaxSize; batchNum ++){
            auto weatherData = weatherDataCollection->front();

            if(sendPostJsonRequestWithLogging(
                _config.ServerHost, 
                _config.ServerApiPostWeatherDataUrl,
                weatherData.toJson()))
                {
                    weatherDataCollection->pop();
                }
            yield();
        }
        
        disconnectWifi();
        return true;
    }   
    return false;
}

bool BackendClient::SendSystemStatusReports(std::queue<SystemHealthReport>* reportsCollection){
    if(reportsCollection->size() == 0) return true;

    if(connectWifi()){
        for(int batchNum = 0; batchNum < _config.BatchRequestsMaxSize; batchNum ++){
            auto healthReport = reportsCollection->front();

            if(sendPostJsonRequestWithLogging(
                _config.ServerHost, 
                _config.ServerApiPostHealthStatusUrl,
                healthReport.toJson()))
                {
                    reportsCollection->pop();
                }
            yield();
        }
        
        disconnectWifi();
        return true;
    }   
    return false;
}

bool BackendClient::sendPostJsonRequestWithLogging(const char* host, const char* resource, String jsonPayload){
    HttpResponse response = _esp->sendPostJsonRequest(
        host, 
        resource,
        jsonPayload);

    if(!response.success){
        globalSystemState->addError(
            SystemErrorCode::Network_BackendServerConnectionFailure, 
            SystemErrorSeverity::SystemWarning, 
            "Endpoint '"+ String(resource) +"' connection failed");
    }
    else globalSystemState->removeError(SystemErrorCode::Network_BackendServerConnectionFailure);

    if(response.statusCode != 200){
        globalSystemState->addError(
            SystemErrorCode::Network_BackendServerInternalError, 
            SystemErrorSeverity::SystemWarning, 
            "Endpoint '"+ String(resource) +"' responded " + String(response.statusCode));
    }
    else globalSystemState->removeError(SystemErrorCode::Network_BackendServerInternalError);

    return response.statusCode == 200;
}

bool BackendClient::connectWifi(){
    bool isConnected = _esp->connectWifi(_config.WifiSSID, _config.WifiPassword);
    if(!isConnected){
        globalSystemState->addError(
            SystemErrorCode::Network_WifiConnectionFailure, 
            SystemErrorSeverity::SystemWarning, 
            "Wifi connection failed");
    }
    else globalSystemState->removeError(SystemErrorCode::Network_WifiConnectionFailure);

    return isConnected;
}

void BackendClient::disconnectWifi(){
    _esp->disconnectWifi();
}