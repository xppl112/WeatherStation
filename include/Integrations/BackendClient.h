#include <queue>
#include "EspWifiClient.h"
#include "Config.h"
#include "Models/WeatherMonitorData.h"

enum class BackendResponseStatus {SUCCESS, SYSTEM_ERROR, WIFI_CANT_CONNECT, BACKEND_ERROR, BACKEND_TIMEOUT};

class BackendClient
{
public:
    BackendClient(BackendClientConfig config);
    bool SendWeatherData(std::queue<WeatherMonitorData>* weatherDataCollection);
    int GetServerTime();

private:
    bool connectWifi();
    void disconnectWifi();
    bool sendPostJsonRequestWithLogging(const char* host, const char* resource, String jsonPayload);
    BackendClientConfig _config;
    EspWifiClient* _esp;
};