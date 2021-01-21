#include "Healthchecks/HealthcheckProvider.h"


HealthcheckProvider::HealthcheckProvider(HardwareModulesRegistry* hardwareModulesRegistry){
    _hardwareModulesRegistry = hardwareModulesRegistry;
}

void HealthcheckProvider::checkSystemHealth(){

}

SystemHealthStatus HealthcheckProvider::getSystemHealth(){

}