#include "Integrations/BackendClient.h"

BackendClient::BackendClient(BackendClientConfig config){
    _config = config;
    _esp = new EspWifiClient();
}

bool BackendClient::SendWeatherData(WeatherMonitorData weatherData) {
    if(connectWifi()){
        HttpResponse response = _esp->sendPostJsonRequest(
            _config.ServerHost, 
            _config.ServerApiPostWeatherDataUrl,
            weatherData.toJson());

        disconnectWifi();
        return response.statusCode == 200;
    }

    //TODO: ERROR WIFI CONNECTION    
    return false;
}

int BackendClient::GetServerTime(){
    connectWifi();
    HttpResponse response = _esp->sendGetRequest(
        _config.ServerHost, 
        _config.ServerApiGetTimeUrl);
    disconnectWifi();
    return atoi(response.payload.c_str());
}

bool BackendClient::connectWifi(){
    return _esp->connectWifi(_config.WifiSSID, _config.WifiPassword);
}

void BackendClient::disconnectWifi(){
    _esp->disconnectWifi();
}