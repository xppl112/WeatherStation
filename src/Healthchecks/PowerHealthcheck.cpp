#include "Healthchecks/PowerHealthcheck.h"
#include "SystemUtils.h"
#include "Config.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

PowerHealthcheck::PowerHealthcheck(){
}

HealthStatus PowerHealthcheck::check(){
    HealthStatus status = HealthStatus::HEALTH_OK;
    float inputVoltage = getInputVoltage();
    if(inputVoltage >= VOLTMETER_ALERT_THRESHOLD_DANGEROUS)
        status = HealthStatus::HEALTH_ERROR;
    else if(inputVoltage >= VOLTMETER_ALERT_THRESHOLD_TOP || inputVoltage < VOLTMETER_ALERT_THRESHOLD_BOTTOM)
        status = HealthStatus::HEALTH_WARNING;

    handleCheckStatus(status);
    return status;
}

float PowerHealthcheck::getInputVoltage(){
    return SystemUtils::getVoltageFromAnalogPin(VOLTMETER_ANALOG_PIN, VOLTMETER_R1, VOLTMETER_R2);
}

void PowerHealthcheck::handleCheckStatus(HealthStatus healthStatus){
    switch (healthStatus)
    {
        case HealthStatus::HEALTH_WARNING:
            globalSystemState->setPowerStatus(PowerStatus::Warning);break;
        case HealthStatus::HEALTH_ERROR:
            globalSystemState->setPowerStatus(PowerStatus::DangerousVoltage);break;
        default:
            globalSystemState->setPowerStatus(PowerStatus::Regular);
    } 
}