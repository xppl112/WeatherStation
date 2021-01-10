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
    MenuManager* _menuManager;
    ScreenController* _screen;
    LEDIndicatorsController* _ledIndicators;
};