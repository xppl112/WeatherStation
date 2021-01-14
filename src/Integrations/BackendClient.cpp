#include "Integrations/BackendClient.h"

BackendClient::BackendClient(BackendClientConfig config){
    _config = config;
    _esp = new EspWifiClient(&Serial);
}

void BackendClient::resetModule(){
    _esp->initEsp();
}

bool BackendClient::SendWeatherData(WeatherMonitorData weatherData) {    
    connectWifi();
    HttpResponse response = _esp->sendPostJsonRequest(
        _config.ServerHost, 
        _config.ServerPort, 
        _config.ServerApiPostWeatherDataUrl,
        weatherData.serializeJson());

    disconnectWifi();
    return response.statusCode == 200;
}

int BackendClient::GetServerTime(){
    connectWifi();
    HttpResponse response = _esp->sendGetRequest(
        _config.ServerHost, 
        _config.ServerPort, 
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