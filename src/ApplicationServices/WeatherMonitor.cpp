#include "ApplicationServices/WeatherMonitor.h"
#include "Config.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

WeatherMonitor::WeatherMonitor(HardwareModulesRegistry* hardwareModulesRegistry){
    _hardwareModulesRegistry = hardwareModulesRegistry;
    _timer = new Ticker(0);
}

void WeatherMonitor::run(){
    state = IDLE;
    _timer->start();    
}

void WeatherMonitor::updateTimers(){
    _timer->update();

    if(_timer->state() == FIRED){
        if(state == IDLE)startMeasuring();
        else if(state == MEASURING)finishMeasuring();
        _timer->resetStatus();
    }
}

void WeatherMonitor::addUpdatedEventHandler(WeatherMonitorUpdatedEventCallback callback){
    _onUpdateCallback = callback;
}

void WeatherMonitor::startMeasuring(){
    _timer->interval(WEATHER_MONITOR_MEASUREMENT_DURATION_SECONDS * 1000);
    state = MEASURING;    
    globalSystemState->setSystemStatus(GlobalSystemState::SystemStatus::Measuring);    
    _startMeasuringTimestamp = globalSystemState->getCurrentTimestamp();
    
    _hardwareModulesRegistry->airParticiplesSensor->beginMeasurement();
}

void WeatherMonitor::finishMeasuring(){
    _timer->interval(WEATHER_MONITOR_INTERVAL_SECONDS * 1000);
    WeatherMonitorData data {.isDataReceived = false};

    PmsData airParticiplesData = _hardwareModulesRegistry->airParticiplesSensor->endMeasurement();
    BME280Data outdoorMeteoData = _hardwareModulesRegistry->outdoorMeteoSensor->getData();
    DHTData indoorMeteoData = _hardwareModulesRegistry->indoorMeteoSensor->getData();

    if(airParticiplesData.isDataReceived || outdoorMeteoData.isDataReceived || indoorMeteoData.isDataReceived){
        data.isDataReceived = true;
        data.timeStampOfStart = _startMeasuringTimestamp;
        data.timeStampOfFinish = globalSystemState->getCurrentTimestamp();
    }

    if(airParticiplesData.isDataReceived){
        data.PM1_0 = airParticiplesData.PM_1_0;
        data.PM2_5 = airParticiplesData.PM_2_5;
        data.PM_10_0 = airParticiplesData.PM_10_0;
    }

    if(outdoorMeteoData.isDataReceived){
        data.temperatureOutside = outdoorMeteoData.temperatureCelsium;
        data.humidityOutside = outdoorMeteoData.humidityPercent;
        data.pressureOutside = outdoorMeteoData.pressureInHPascals;
    }

    if(indoorMeteoData.isDataReceived){
        data.temperatureInside = indoorMeteoData.temperatureCelsium;
        data.humidityInside = indoorMeteoData.humidityPercent;
    }

    state = IDLE;
    globalSystemState->setSystemStatus(GlobalSystemState::SystemStatus::Idle);    
    if(_onUpdateCallback != NULL) _onUpdateCallback(data);
}