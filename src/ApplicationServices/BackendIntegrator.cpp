#include "ApplicationServices/BackendIntegrator.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "Config.h"
extern GlobalSystemState* globalSystemState;

BackendIntegrator::BackendIntegrator(){
    _backendClient = new BackendClient();

    _timeUpdateTimer = new Ticker(1 * 1000, NULL, MILLIS);
    _timeUpdateTimer->start(true); 
}
   
void BackendIntegrator::updateTimers(){
    _timeUpdateTimer->update();

    if(_timeUpdateTimer->state() == FIRED){
        if(!updateServerTime())
            _timeUpdateTimer->resetStatus();
    }
}

bool BackendIntegrator::updateServerTime(){
    unsigned long serverTimestamp = _backendClient->GetServerTime();
    if(serverTimestamp != 0) globalSystemState->updateTime(serverTimestamp);  
    return serverTimestamp != 0;
}

void BackendIntegrator::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    collectWeatherUpdate(weatherMonitorData);

    if(!globalSystemState->isNightMode ||
       !(globalSystemState->isNightMode && skippedCyclesCount < SKIP_SENDING_DATA_CYCLES_IN_NIGHT_MODE)){
        auto serverResponse = _backendClient->SynchronizeData(&_weatherMonitorDataCollection);
        if(serverResponse.dataReceived){
            globalSystemState->updateTime(serverResponse.timeStamp);
            globalSystemState->setNightMode(serverResponse.isNightMode);
        }
        skippedCyclesCount = 0;
    }
    else skippedCyclesCount++;
 
    globalSystemState->unsyncronizedWeatherReports = _weatherMonitorDataCollection.size();
}

void BackendIntegrator::collectWeatherUpdate(WeatherMonitorData weatherMonitorData){
    _weatherMonitorDataCollection.push_back(weatherMonitorData);
    if(_weatherMonitorDataCollection.size() > DATA_COLLECTION_CAPACITY)_weatherMonitorDataCollection.erase(_weatherMonitorDataCollection.begin());
}