#include "ApplicationServices/SystemModeController.h"
#include "DateTimeUtils.h"
#include "Config.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

SystemModeController::SystemModeController(){   
    _nightModeTimer = new Ticker(LIGHT_SCAN_INTERVAL_SECONDS * 1000, NULL, MILLIS);
    _nightModeTimer->start();
}

void SystemModeController::refresh() {   
    _nightModeTimer->update();

    if(_nightModeTimer->state() == FIRED){
        checkNightMode();
        _nightModeTimer->resetStatus();
    }    
}

void SystemModeController::checkNightMode() {   
     
    //TODO
    if(true){
        globalSystemState->setNightMode(true);
    }
    else {
        globalSystemState->setNightMode(false);
    }
}