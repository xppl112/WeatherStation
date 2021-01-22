#include <Arduino.h>
#include "ApplicationServices/WeatherMonitor.h"
#include "ApplicationServices/UIController.h"
#include "ApplicationServices/BackendIntegrator.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "HardwareModules/HardwareModulesRegistry.h"
#include "Healthchecks/HealthcheckProvider.h"

GlobalSystemState* globalSystemState;
HardwareModulesRegistry* hardwareModulesRegistry;
WeatherMonitor* weatherMonitor;
UIController* uiController;
BackendIntegrator* backendIntegrator;
HealthcheckProvider* healthcheckProvider;
void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData);

void setup() {
    globalSystemState = new GlobalSystemState();
    hardwareModulesRegistry = new HardwareModulesRegistry();
    hardwareModulesRegistry->reconnectAllDevices();    
    healthcheckProvider = new HealthcheckProvider(hardwareModulesRegistry);

    uiController = new UIController(hardwareModulesRegistry, healthcheckProvider);
    weatherMonitor = new WeatherMonitor(hardwareModulesRegistry);
    backendIntegrator = new BackendIntegrator();    

    weatherMonitor->addUpdatedEventHandler(onWeatherUpdatedEventHandler);
    weatherMonitor->run();
}

void loop() {
    healthcheckProvider->checkSystemHealth();
    uiController->updateUI();
    weatherMonitor->updateTimers();
    backendIntegrator->updateTimers();
}

void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData){
    uiController->onWeatherUpdated(weatherMonitorData);
    //backendIntegrator->onWeatherUpdated(weatherMonitorData);
}