#include "ApplicationServices/SystemModeController.h"
#include "DateTimeUtils.h"
#include "Config.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

SystemModeController::SystemModeController(HardwareModulesRegistry* hardwareModulesRegistry){ 
    _lightSensor = hardwareModulesRegistry->lightSensor;
    _nightModeTimer = new Ticker(SENSORS_SCAN_INTERVAL_SECONDS * 1000, NULL, MILLIS);
    _nightModeTimer->start();
}

void SystemModeController::sleep() {
    //TODO: sleep logic with interuption by button
    //sleep for SENSORS_SCAN_INTERVAL_SECONDS
    delay(SENSORS_SCAN_INTERVAL_SECONDS*1000);
}

void SystemModeController::refresh() {   
    _nightModeTimer->update();

    if(_nightModeTimer->state() == FIRED){
        checkLightLevel();
        _nightModeTimer->resetStatus();
    }    
}

void SystemModeController::checkLightLevel() {   
    auto lightLevel = _lightSensor->getLightLevel();
    //30 - maximum for daylight conditions. Recalculate accordingly
    if(lightLevel > 30) lightLevel = 30;
    lightLevel = lightLevel * 100 / 30;
    globalSystemState->setLightLevel(lightLevel);

    //Use Server response to set night mode
/*
    if(lightLevel <= 10){
        globalSystemState->setNightMode(true);
    }
    else {
        globalSystemState->setNightMode(false);
    }*/
}