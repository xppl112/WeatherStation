#include "Healthchecks/HealthcheckProvider.h"


HealthcheckProvider::HealthcheckProvider(HardwareModulesRegistry* hardwareModulesRegistry);
void HealthcheckProvider::checkSystemHealth();
SystemHealthStatus HealthcheckProvider::getSystemHealth();
