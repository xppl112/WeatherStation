#include <Arduino.h>
#include "ApplicationServices/WeatherMonitor.h"
#include "ApplicationServices/UIController.h"
#include "ApplicationServices/BackendIntegrator.h"
#include "ApplicationServices/SystemModeController.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "HardwareModules/HardwareModulesRegistry.h"
#include "Healthchecks/HealthcheckController.h"

GlobalSystemState* globalSystemState;
HardwareModulesRegistry* hardwareModulesRegistry;
WeatherMonitor* weatherMonitor;
UIController* uiController;
BackendIntegrator* backendIntegrator;
HealthcheckController* healthcheckController;
SystemModeController* systemModeController;
void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData);
void onSystemStateUpdatedEventHandler();

void setup() { 
    globalSystemState = new GlobalSystemState();
    hardwareModulesRegistry = new HardwareModulesRegistry();
    hardwareModulesRegistry->reconnectAllDisconnectedDevices(true);    
    healthcheckController = new HealthcheckController(hardwareModulesRegistry);

    uiController = new UIController(hardwareModulesRegistry, healthcheckController);
    weatherMonitor = new WeatherMonitor(hardwareModulesRegistry);
    backendIntegrator = new BackendIntegrator(healthcheckController); 
    systemModeController = new SystemModeController(); 
 
    hardwareModulesRegistry->reconnectAllDisconnectedDevices(false);  
    weatherMonitor->addUpdatedEventHandler(onWeatherUpdatedEventHandler);
    weatherMonitor->run();

    globalSystemState->addUpdatedEventHandler(onSystemStateUpdatedEventHandler);
}

void loop() {
    try {
        healthcheckController->updateTimers();
        uiController->updateUI();
        weatherMonitor->updateTimers();
        systemModeController->refresh();
        backendIntegrator->updateTimers();
    }
    catch(const std::exception& e){
        globalSystemState->addError(
            SystemErrorCode::CriticalException,
            SystemErrorSeverity::SystemError,
            "main::loop: " + String(e.what())
        );       
    }
    catch (...) {
        globalSystemState->addError(
            SystemErrorCode::CriticalException,
            SystemErrorSeverity::SystemError,
            "main::loop");  
    }
}

void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData){
    uiController->onWeatherUpdated(weatherMonitorData);
    backendIntegrator->onWeatherUpdated(weatherMonitorData);
}

void onSystemStateUpdatedEventHandler(){
    uiController->updateUI();
}