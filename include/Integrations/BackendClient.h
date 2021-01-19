#include "EspWifiClient.h"
#include "Config.h"
#include "Models/WeatherMonitorData.h"

enum BackendResponseStatus {SUCCESS, SYSTEM_ERROR, WIFI_CANT_CONNECT, BACKEND_ERROR, BACKEND_TIMEOUT};

class BackendClient
{
public:
    BackendClient(BackendClientConfig config);
    bool SendWeatherData(WeatherMonitorData weatherData);
    int GetServerTime();

private:
    bool connectWifi();
    void disconnectWifi();
    BackendClientConfig _config;
    EspWifiClient* _esp;
};