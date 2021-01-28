#ifndef HardwareDevicesHealthcheck_H
#define HardwareDevicesHealthcheck_H

#include <map>
#include "HardwareModules/HardwareModulesRegistry.h"
#include "Healthchecks/IHealthcheck.h"

enum class HardwareDeviceStatus {NO_REGISTERED, CONNECTED, DISCONNECTED, FAILURE};

class HardwareDevicesHealthcheck : public IHealthcheck
{
public:
    HardwareDevicesHealthcheck(HardwareModulesRegistry* hardwareModulesRegistry);
    HealthStatus check() override;

    std::map<HardwareDeviceId, HardwareDeviceStatus> getDevicesStatus();

private:
    HardwareModulesRegistry* _hardwareModulesRegistry;
    std::map<HardwareDeviceId, HardwareDeviceStatus> _hardwareDevicesHealthStatus;

    void handleCheckStatus(HealthStatus healthStatus) override;
};

#endif