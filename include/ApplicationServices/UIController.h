#include "HardwareModules/HardwareModulesRegistry.h"
#include "UI/LEDIndicatorsController.h"
#include "UI/MenuController.h"
#include "UI/ScreenController.h"
#include "UI/InputsController.h"
#include "Models/WeatherMonitorData.h"

class UIController
{
public:
    UIController(HardwareModulesRegistry* hardwareModulesRegistry);
    void updateUI();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);
    void enableMenuMode(bool debugMode = false);
    void disableMenuMode();

private:
    enum ScreenMode {OFF, TEMPERATURE_OUTSIDE, AIR_POLLUTION, METEO_OUTSIDE, METEO_INSIDE, AIR_QULITY};
    void updateInputs();
    void showCurrentWeather();
    void flipScreenMode(bool forward);

    MenuController* _menuController;
    ScreenController* _screen;
    LEDIndicatorsController* _ledIndicators;
    InputsController* _inputsController;

    WeatherMonitorData _currentWeather;
    bool _isNightMode = false;
    bool _isMenuMode = false;
    ScreenMode _currentScreenMode = TEMPERATURE_OUTSIDE;
};