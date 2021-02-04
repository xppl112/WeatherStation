#include "HardwareModules/HardwareModulesRegistry.h"
#include "UI/LEDIndicatorsController.h"
#include "UI/MenuController.h"
#include "UI/ScreenController.h"
#include "UI/InputsController.h"
#include "Models/WeatherMonitorData.h"
#include "Healthchecks/HealthcheckController.h"

class UIController
{
public:
    UIController(HardwareModulesRegistry* hardwareModulesRegistry, HealthcheckController* healthcheckController);
    void updateUI();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);
    void enableMenuMode(bool debugMode = false);
    void disableMenuMode();

private:
    enum class ScreenMode {OFF, TEMPERATURE_OUTSIDE, AIR_POLLUTION, METEO_OUTSIDE, METEO_INSIDE, AIR_QULITY};
    void updateInputs();
    void showCurrentWeather();
    void flipScreenMode(bool forward);

    MenuController* _menuController;
    ScreenController* _screen;
    LEDIndicatorsController* _ledIndicators;
    InputsController* _inputsController;

    WeatherMonitorData _currentWeather;
    bool _isMenuMode = false;
    unsigned long _lastUserInteractionTimestamp = 0;
    bool _isUserInteracts = false;
    ScreenMode _currentScreenMode = ScreenMode::TEMPERATURE_OUTSIDE;
};