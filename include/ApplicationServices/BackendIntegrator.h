#include <queue>
#include "Integrations/BackendClient.h"
#include "Ticker.h"

class BackendIntegrator
{
public:
    BackendIntegrator();
    void updateTimers();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);
    void resetModule();

private:
    BackendClient* _backendClient;
    Ticker* _timeUpdateTimer;
    uint8_t skippedCyclesCount = 0;
    
    bool updateServerTime();
    
    std::vector<WeatherMonitorData> _weatherMonitorDataCollection;

    void collectWeatherUpdate(WeatherMonitorData weatherMonitorData);
};
