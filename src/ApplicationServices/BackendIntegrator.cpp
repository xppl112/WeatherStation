#include "ApplicationServices/BackendIntegrator.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "Config.h"
extern GlobalSystemState* globalSystemState;

BackendIntegrator::BackendIntegrator(){
    BackendClientConfig config;
    _backendClient = new BackendClient(config);

    _timeUpdateTimer = new Ticker(TIME_UPDATE_INTERVAL_SECONDS * 1000, NULL, MILLIS);
    _timeUpdateTimer->start(true); 
}
   
void BackendIntegrator::updateTimers(){
    _timeUpdateTimer->update();

    if(_timeUpdateTimer->state() == FIRED){
        if(!globalSystemState->isNightMode)updateServerTime();
        _timeUpdateTimer->resetStatus();
    }    
}

void BackendIntegrator::updateServerTime(){
    int serverTimestamp = _backendClient->GetServerTime();
    if(serverTimestamp != -1) globalSystemState->updateTime(serverTimestamp);  
}

void BackendIntegrator::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    collectWeatherUpdate(weatherMonitorData);

    if(!globalSystemState->isNightMode){
        _backendClient->SendWeatherData(&_weatherMonitorDataCollection);   
    }
 
    globalSystemState->unsyncronizedWeatherReports = _weatherMonitorDataCollection.size();
}

void BackendIntegrator::collectWeatherUpdate(WeatherMonitorData weatherMonitorData){
    _weatherMonitorDataCollection.push(weatherMonitorData);
    if(_weatherMonitorDataCollection.size() > DATA_COLLECTION_CAPACITY)_weatherMonitorDataCollection.pop();
}