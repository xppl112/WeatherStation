#include <Arduino.h>
#include "ApplicationServices/WeatherMonitor.h"
#include "ApplicationServices/UIController.h"
#include "ApplicationServices/BackendIntegrator.h"
#include "ApplicationServices/SystemModeController.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "HardwareModules/HardwareModulesRegistry.h"

GlobalSystemState* globalSystemState;
HardwareModulesRegistry* hardwareModulesRegistry;
WeatherMonitor* weatherMonitor;
UIController* uiController;
BackendIntegrator* backendIntegrator;
SystemModeController* systemModeController;
void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData);
void onSystemStateUpdatedEventHandler();

void setup() { 
    globalSystemState = new GlobalSystemState();
    hardwareModulesRegistry = new HardwareModulesRegistry();
    hardwareModulesRegistry->reconnectAllDisconnectedDevices(true);

    uiController = new UIController(hardwareModulesRegistry);
    weatherMonitor = new WeatherMonitor(hardwareModulesRegistry);
    backendIntegrator = new BackendIntegrator(); 
    systemModeController = new SystemModeController(); 
 
    hardwareModulesRegistry->reconnectAllDisconnectedDevices(false);  
    weatherMonitor->addUpdatedEventHandler(onWeatherUpdatedEventHandler);
    weatherMonitor->run();
}

void loop() {
    uiController->updateUI();
    weatherMonitor->updateTimers();
    systemModeController->refresh();
    backendIntegrator->updateTimers();
}

void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData){
    uiController->onWeatherUpdated(weatherMonitorData);
    backendIntegrator->onWeatherUpdated(weatherMonitorData);
}