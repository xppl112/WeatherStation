#include "Healthchecks/HealthcheckProvider.h"

HealthcheckProvider::HealthcheckProvider(HardwareModulesRegistry* hardwareModulesRegistry){
    _hardwareDevicesHealthcheck = new HardwareDevicesHealthcheck(hardwareModulesRegistry);
}

void HealthcheckProvider::checkSystemHealth(){
    
}

SystemHealthStatus HealthcheckProvider::getSystemHealth(){

}