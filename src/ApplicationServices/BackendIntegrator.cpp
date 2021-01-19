#include "ApplicationServices/BackendIntegrator.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "Config.h"
extern GlobalSystemState* globalSystemState;

BackendIntegrator::BackendIntegrator(){
    BackendClientConfig config;
    _backendClient = new BackendClient(config);
}
   
void BackendIntegrator::updateTimers(){

}

unsigned long BackendIntegrator::getServerTime(){
    return _backendClient->GetServerTime();
}

void BackendIntegrator::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    globalSystemState->setSystemStatus(GlobalSystemState::SystemStatus::DataTransfer);  

    _backendClient->SendWeatherData(weatherMonitorData);

    globalSystemState->setSystemStatus(GlobalSystemState::SystemStatus::Idle);    
}