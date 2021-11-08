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
            return -1;
        }

        if(response.statusCode == 200){
            return atoi(response.payload.c_str());
        }
    }

    return -1;
}

bool BackendClient::SendWeatherData(std::queue<WeatherMonitorData>* weatherDataCollection) {
    if(weatherDataCollection->size() == 0) return true;

    if(connectWifi()){
        for(int batchNum = 0; batchNum < _config.BatchRequestsMaxSize; batchNum++){
            if(weatherDataCollection->size() == 0)break;
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

bool BackendClient::sendPostJsonRequestWithLogging(const char* host, const char* resource, String jsonPayload){
    HttpResponse response = _esp->sendPostJsonRequest(
        host, 
        resource,
        jsonPayload);

    if(!response.success){
        return false;
    }

    return response.statusCode == 200;
}

bool BackendClient::connectWifi(){
    bool isConnected = _esp->connectWifi(_config.WifiSSID, _config.WifiPassword);
    return isConnected;
}

void BackendClient::disconnectWifi(){
    _esp->disconnectWifi();
}