#include "Healthchecks/HardwareDevicesHealthcheck.h"

HardwareDevicesHealthcheck::HardwareDevicesHealthcheck(HardwareModulesRegistry* hardwareModulesRegistry){
    _hardwareModulesRegistry = hardwareModulesRegistry;
}

void HardwareDevicesHealthcheck::check(){
    getDevicesConnectionStatus();
}

void HardwareDevicesHealthcheck::getDevicesConnectionStatus(){
    _hardwareModulesRegistry->airParticiplesSensor->isConnected();
}