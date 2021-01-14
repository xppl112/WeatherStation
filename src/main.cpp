#include <Arduino.h>
#include "ApplicationServices/WeatherMonitor.h"
#include "ApplicationServices/UIController.h"
#include "ApplicationServices/BackendIntegrator.h"
#include "Models/GlobalSystemState.h"

GlobalSystemState* globalSystemState;
WeatherMonitor* weatherMonitor;
UIController* uiController;
BackendIntegrator* backendIntegrator;
void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData);

void setup() {
    globalSystemState = new GlobalSystemState();

    uiController = new UIController();
    weatherMonitor = new WeatherMonitor();
    backendIntegrator = new BackendIntegrator();

    weatherMonitor->addUpdatedEventHandler(onWeatherUpdatedEventHandler);
    weatherMonitor->run();
}

void loop() {
    uiController->updateInputs();
    weatherMonitor->updateTimers();
    backendIntegrator->updateTimers();
}

void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData){
    uiController->onWeatherUpdated(weatherMonitorData);
    backendIntegrator->onWeatherUpdated(weatherMonitorData);
}