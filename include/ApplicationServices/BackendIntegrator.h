#include "Integrations/BackendClient.h"

class BackendIntegrator
{
public:
    BackendIntegrator();
    void updateTimers();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);
    void resetModule();

private:
    BackendClient* _backendClient;
};
