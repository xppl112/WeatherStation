#include "Healthchecks/HealthcheckController.h"
#include "Config.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

HealthcheckController::HealthcheckController(HardwareModulesRegistry* hardwareModulesRegistry){
    hardwareDevicesHealthcheck = new HardwareDevicesHealthcheck(hardwareModulesRegistry);
    networkingHealthcheck = new NetworkingHealthcheck();    
    softwareHealthcheck = new SoftwareHealthcheck();    
    _hardwareModulesRegistry = hardwareModulesRegistry;
    
    _healthchecks.push_back(hardwareDevicesHealthcheck);
    _healthchecks.push_back(networkingHealthcheck);
    _healthchecks.push_back(softwareHealthcheck);

    _timer = new Ticker(HEALTHCHECK_MONITOR_INTERVAL_SECONDS * 1000, NULL, MILLIS);
    _timer->start(true);
}

void HealthcheckController::updateTimers() {
    _timer->update();

    if(_timer->state() == FIRED){        
        checkSystemHealth();
        _timer->resetStatus();
    }    
}

void HealthcheckController::checkSystemHealth(){
    _healthStatus = HealthStatus::HEALTH_OK;

    for(auto healthcheck : _healthchecks){
        auto status = healthcheck->check();
        if((int)status > (int)_healthStatus)_healthStatus = status;
    }
    globalSystemState->systemHealth = _healthStatus;
}

HealthStatus HealthcheckController::getSystemHealth(){
    return _healthStatus;
}

SystemHealthReport HealthcheckController::getSystemHealthReport(){
    SystemHealthReport report;
    report.timeStamp = globalSystemState->getCurrentTimestamp();
    report.systemHealth = globalSystemState->systemHealth;
    report.powerStatus = globalSystemState->powerStatus;    
    report.inputVoltage = 0;
    report.networkingStatus = networkingHealthcheck->getStatus();

    report.systemErrors = globalSystemState->getAllErrors();

    auto devicesStatuses = hardwareDevicesHealthcheck->getDevicesStatus();
    for(auto deviceStatus : devicesStatuses){
        auto device = _hardwareModulesRegistry->getDevice(deviceStatus.first);
        if(device != NULL){
            report.hardwareDevices[device->getInfo().Name] = deviceStatus.second;
        }
    }

    return report;
}