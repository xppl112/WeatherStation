#include "Healthchecks/HardwareDevicesHealthcheck.h"

HardwareDevicesHealthcheck::HardwareDevicesHealthcheck(HardwareModulesRegistry* hardwareModulesRegistry){
    _hardwareModulesRegistry = hardwareModulesRegistry;
}

HealthStatus HardwareDevicesHealthcheck::check(){
    std::map<HardwareDeviceId, HardwareDeviceStatus> devicesStatus;
    HealthStatus healthStatus = HealthStatus::HEALTH_OK;

    bool allDisconnected = true;
    for (auto module : _hardwareModulesRegistry->hardwareModules) {        
        if(module.second->isConnected()){
            devicesStatus[module.first] = HardwareDeviceStatus::CONNECTED;
            allDisconnected = false;
        }
        else {
            devicesStatus[module.first] = HardwareDeviceStatus::DISCONNECTED;
            healthStatus = HealthStatus::HEALTH_WARNING;
        }        
    }

    if(allDisconnected)healthStatus = HealthStatus::HEALTH_ERROR;

    _hardwareDevicesHealthStatus.clear();
    _hardwareDevicesHealthStatus = devicesStatus;

    handleCheckStatus(healthStatus);
    return healthStatus;
}

std::map<HardwareDeviceId, HardwareDeviceStatus> HardwareDevicesHealthcheck::getDevicesStatus(){
    return _hardwareDevicesHealthStatus;
}

void HardwareDevicesHealthcheck::handleCheckStatus(HealthStatus healthStatus){
    if(healthStatus != HealthStatus::HEALTH_OK){
        for (auto module : _hardwareDevicesHealthStatus) {
            if(module.second == HardwareDeviceStatus::DISCONNECTED || module.second == HardwareDeviceStatus::FAILURE){
                _hardwareModulesRegistry->resetDevice(module.first);
            }
        }

        _hardwareModulesRegistry->reconnectAllDisconnectedDevices();
    }
}