#include <queue>
#include "EspWifiClient.h"
#include "Config.h"
#include "Models/WeatherMonitorData.h"
#include "Models/SynchronizationDataResponse.h"

enum class BackendResponseStatus {SUCCESS, SYSTEM_ERROR, WIFI_CANT_CONNECT, BACKEND_ERROR, BACKEND_TIMEOUT};

class BackendClient
{
public:
    BackendClient();
    SynchronizationDataResponse SynchronizeData(std::vector<WeatherMonitorData>* weatherDataCollection);
    unsigned long GetServerTime();

private:
    bool connectWifi();
    void disconnectWifi();
    HttpResponse sendPostJsonRequest(const char* host, const char* resource, String jsonPayload);
    BackendClientConfig _config;
    EspWifiClient* _esp;
};