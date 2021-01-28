#include "HardwareModules/HardwareModulesRegistry.h"
#include "RGBLed.h"
#include "MCPExtender.h"
#include "Models/WeatherMonitorData.h"
#include <Ticker.h>

class LEDIndicatorsController
{
public:
    LEDIndicatorsController(HardwareModulesRegistry* hardwareModulesRegistry);
    void setPollutionLevel(WeatherMonitorData weatherData);
    void setWeatherStatusLed(WeatherMonitorData weatherData);
    void updateSystemStatusLed();
    void clearAllIndicators();

private:
    RGBLed* _pollutionRGBLed;
    MCPExtender* _mcp;

    Ticker* _timerSlow;
    Ticker* _timerFast;
    bool _fastBlinkingLedOn = false;
    bool _slowBlinkingLedOn = false;
};