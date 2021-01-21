#ifndef HealthcheckProvider_H
#define HealthcheckProvider_H

#include "HardwareModules/HardwareModulesRegistry.h"
#include "Healthchecks/HardwareDevicesHealthcheck.h"

enum SystemHealthStatus {HEALTH_OK, HEALTH_WARNING, HEALTH_ERROR};

class HealthcheckProvider
{
public:
    HealthcheckProvider(HardwareModulesRegistry* hardwareModulesRegistry);
    void checkSystemHealth();
    SystemHealthStatus getSystemHealth();

private:
    HardwareDevicesHealthcheck* _hardwareDevicesHealthcheck;
    SystemHealthStatus _healthStatus;
};

#endif