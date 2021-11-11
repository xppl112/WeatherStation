#include "Ticker.h"
#include "HardwareModules/HardwareModulesRegistry.h"

class SystemModeController
{
public:
    SystemModeController(HardwareModulesRegistry* hardwareModulesRegistry);
    void refresh();

private:
    void checkLightLevel();

    Ticker* _nightModeTimer;
    LightSensor* _lightSensor;
};