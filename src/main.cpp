#include <Arduino.h>
#include "ApplicationServices/WeatherMonitor.h"
#include "ApplicationServices/UIController.h"
#include "ApplicationServices/BackendIntegrator.h"

WeatherMonitor* weatherMonitor;
UIController* uiController;
BackendIntegrator* backendIntegrator;
void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData);

void setup() {
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