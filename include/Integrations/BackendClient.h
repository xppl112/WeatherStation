#include "EspWifiClient.h"
#include "config.h"
#include "Models/WeatherMonitorData.h"

enum BackendResponseStatus {OK, ESP_ERROR, WIFI_CANT_CONNECT, BACKEND_ERROR, BACKEND_TIMEOUT};

class BackendClient
{
public:
    BackendClient(BackendClientConfig config);
    void resetModule();
    bool SendWeatherData(WeatherMonitorData weatherData);
    int GetServerTime();

private:
    bool connectWifi();
    void disconnectWifi();
    BackendClientConfig _config;
    EspWifiClient* _esp;
};