#include "ApplicationServices/BackendIntegrator.h"
#include "config.h"

BackendIntegrator::BackendIntegrator(){
    BackendClientConfig config;
    _backendClient = new BackendClient(config);
    resetModule();
}
   
void BackendIntegrator::updateTimers(){

}

unsigned long BackendIntegrator::getServerTime(){
    return _backendClient->GetServerTime();
}

void BackendIntegrator::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    _backendClient->SendWeatherData(weatherMonitorData);
}

void BackendIntegrator::resetModule(){
    _backendClient->resetModule();
}