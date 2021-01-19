#include "UI/LEDIndicatorsController.h"
#include "UI/MenuManager.h"
#include "UI/ScreenController.h"
#include "UI/InputsController.h"
#include "Models/WeatherMonitorData.h"

class UIController
{
public:
    UIController();
    void updateUI();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);

private:
    enum ScreenMode {OFF, TEMPERATURE_OUTSIDE, AIR_POLLUTION, METEO_OUTSIDE, METEO_INSIDE, AIR_QULITY};
    void updateInputs();
    void showCurrentWeather();
    void flipScreenMode(bool forward);

    MenuManager* _menuManager;
    ScreenController* _screen;
    LEDIndicatorsController* _ledIndicators;
    InputsController* _inputsController;

    WeatherMonitorData _currentWeather;
    bool _isNightMode = false;
    ScreenMode _currentScreenMode = TEMPERATURE_OUTSIDE;
};