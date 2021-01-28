#include "ApplicationServices/SystemModeController.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

SystemModeController::SystemModeController(){   
    _nightModeTimer = new Ticker(60 * 1000, NULL, MILLIS);
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
      
}