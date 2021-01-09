#include <Arduino.h>
#include "ApplicationServices/WeatherMonitor.h"
#include "ApplicationServices/UIController.h"

WeatherMonitor* weatherMonitor;
UIController* uiController;

void setup() {
    weatherMonitor = new WeatherMonitor();
    uiController = new UIController();
    weatherMonitor->subscribeOnUpdate(uiController->onWeatherUpdated);
    weatherMonitor->subscribeOnUpdate(serverIntegration->onWeatherUpdated);
    //weatherMonitor->OnUpdate(OnWeatherUpdated);
}

void loop() {
    uiController->updateInputs();
}

/*
void onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    uiController->onWeatherUpdated(weatherMonitorData);
    serverIntegration->onWeatherUpdated(weatherMonitorData);
}
*/