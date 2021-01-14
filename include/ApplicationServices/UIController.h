#include "UI/LEDIndicatorsController.h"
#include "UI/MenuManager.h"
#include "UI/ScreenController.h"
#include "Models/WeatherMonitorData.h"

class UIController
{
public:
    UIController();
    void updateInputs();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);

private:
    enum ScreenMode {OFF, TEMPERATURE_OUTSIDE, AIR_POLLUTION, METEO_OUTSIDE, METEO_INSIDE};
    void showCurrentWeather();

    MenuManager* _menuManager;
    ScreenController* _screen;
    LEDIndicatorsController* _ledIndicators;

    WeatherMonitorData _currentWeather;
    bool _isNightMode = false;
    ScreenMode _currentScreenMode = TEMPERATURE_OUTSIDE;
};