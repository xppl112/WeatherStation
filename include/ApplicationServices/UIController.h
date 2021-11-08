#include "HardwareModules/HardwareModulesRegistry.h"
#include "UI/LEDIndicatorsController.h"
#include "UI/InputsController.h"
#include "UI/LEDDisplayController.h"
#include "Models/WeatherMonitorData.h"

class UIController
{
public:
    UIController(HardwareModulesRegistry* hardwareModulesRegistry);
    void updateUI();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);

private:
    enum class LedDisplayMode {OFF, TEMPERATURE_OUTSIDE, HUMIDITY_OUTSIDE, TEMPERATURE_INSIDE, AIR_POLLUTION};
    void updateInputs();
    void redrawUI();

    LEDDisplayController* _ledDisplayController;
    LEDIndicatorsController* _ledIndicators;
    InputsController* _inputsController;

    WeatherMonitorData _currentWeather;
    LedDisplayMode _currentLedDisplayMode = LedDisplayMode::TEMPERATURE_OUTSIDE;
};