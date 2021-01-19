#include <Arduino.h>
#include "ApplicationServices/WeatherMonitor.h"
#include "ApplicationServices/UIController.h"
#include "ApplicationServices/BackendIntegrator.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "GlobalObjects/GlobalDevices.h"

GlobalSystemState* globalSystemState;
GlobalDevices* globalDevices;
WeatherMonitor* weatherMonitor;
UIController* uiController;
BackendIntegrator* backendIntegrator;
void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData);

void setup() {
    globalSystemState = new GlobalSystemState();
    globalDevices = new GlobalDevices();

    uiController = new UIController();
    weatherMonitor = new WeatherMonitor();
    backendIntegrator = new BackendIntegrator();    

    weatherMonitor->addUpdatedEventHandler(onWeatherUpdatedEventHandler);
    weatherMonitor->run();
}

void loop() {
    uiController->updateUI();
    weatherMonitor->updateTimers();
    backendIntegrator->updateTimers();
}

void onWeatherUpdatedEventHandler(WeatherMonitorData weatherMonitorData){
    uiController->onWeatherUpdated(weatherMonitorData);
    //backendIntegrator->onWeatherUpdated(weatherMonitorData);
}