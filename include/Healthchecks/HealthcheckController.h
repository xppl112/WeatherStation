#ifndef HealthcheckController_H
#define HealthcheckController_H

#include "HardwareModules/HardwareModulesRegistry.h"
#include "Healthchecks/HardwareDevicesHealthcheck.h"
#include "Healthchecks/NetworkingHealthcheck.h"
#include "Healthchecks/SoftwareHealthcheck.h"
#include "Healthchecks/PowerHealthcheck.h"
#include "Healthchecks/IHealthcheck.h"
#include "Models/SystemHealthReport.h"
#include <Ticker.h>

class HealthcheckController
{
public:
    HealthcheckController(HardwareModulesRegistry* hardwareModulesRegistry);
    void updateTimers();
    void checkSystemHealth();
    HealthStatus getSystemHealth();
    SystemHealthReport getSystemHealthReport();

    HardwareDevicesHealthcheck* hardwareDevicesHealthcheck;
    NetworkingHealthcheck* networkingHealthcheck;
    SoftwareHealthcheck* softwareHealthcheck;
    PowerHealthcheck* powerHealthcheck;

private:
    HardwareModulesRegistry* _hardwareModulesRegistry;
    HealthStatus _healthStatus;
    Ticker* _timer;

    std::vector<IHealthcheck*> _healthchecks;
};

#endif