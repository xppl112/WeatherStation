#include "ApplicationServices/BackendIntegrator.h"
#include "config.h"

BackendIntegrator::BackendIntegrator(){
    BackendClientConfig config;
    _backendClient = new BackendClient(config);
    resetModule();
}
   
void BackendIntegrator::updateTimers(){

}

void BackendIntegrator::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    _backendClient->GetServerTime();
}

void BackendIntegrator::resetModule(){
    _backendClient->resetModule();
}