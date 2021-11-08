#include "HardwareModules/HardwareModulesRegistry.h"
#include "TM1637LED.h"
#include "Models/WeatherMonitorData.h"

class LEDDisplayController
{
public:
    LEDDisplayController(HardwareModulesRegistry* hardwareModulesRegistry);
    void clearScreen();
    void showOutdoorHumidity(WeatherMonitorData weatherData);
    void showIndoorTemperature(WeatherMonitorData weatherData);
    void showOutdoorTemperature(WeatherMonitorData weatherData);
    void showAirPollution(WeatherMonitorData weatherData);

private:
    TM1637LED* _display;
};