#include "Integrations/BackendClient.h"

BackendClient::BackendClient(BackendClientConfig config){
  _config = config;
  _esp = new EspWifiClient(&Serial);
}

void BackendClient::resetModule(){
  _esp->initEsp();
}


bool BackendClient::SendWeatherData(WeatherMonitorData weatherData) {

}

int BackendClient::GetServerTime(){
  HttpResponse response = _esp->sendGetRequest(_config.ServerHost, _config.ServerPort, _config.ServerApiGetTimeUrl);

}

bool BackendClient::connectWifi(){
  return _esp->connectWifi(_config.WifiSSID, _config.WifiPassword);
}

void BackendClient::disconnectWifi(){
  _esp->disconnectWifi();
}