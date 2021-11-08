#include "HardwareModules/HardwareModulesRegistry.h"
#include "RGBLed.h"
#include "Models/WeatherMonitorData.h"
#include <Ticker.h>

class LEDIndicatorsController
{
public:
    LEDIndicatorsController(HardwareModulesRegistry* hardwareModulesRegistry);
    void setPollutionLevel(WeatherMonitorData weatherData);
    void clearAllIndicators();
    void blinkBlue();

private:
    RGBLed* _pollutionRGBLed;

    Ticker* _timerSlow;
    Ticker* _timerFast;
    bool _fastBlinkingLedOn = false;
    bool _slowBlinkingLedOn = false;
};