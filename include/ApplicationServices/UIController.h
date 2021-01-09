#include <stdint.h>
#include "UI/LEDIndicators.h"
#include "UI/MenuManager.h"
#include "UI/ScreenPrinter.h"

class UIController
{
public:
    UIController();
    void updateInputs();
    void onWeatherUpdated(WeatherMonitorData weatherMonitorData);

private:
    MenuManager* menuManager;
    ScreenPrinter* screenPrinter;
    LEDIndicators* ledIndicators;
};
