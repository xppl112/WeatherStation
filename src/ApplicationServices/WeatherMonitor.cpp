#include "ApplicationServices/WeatherMonitor.h"
#include "config.h"

WeatherMonitor::WeatherMonitor(){
    _timer = new Ticker(0);    
    _airParticiplesSensor = new AirParticiplesSensor(PLANTOWER_RX_PIN, PLANTOWER_TX_PIN);
    _outdoorMeteoSensor = new OutdoorMeteoSensor(BME_I2C_ADDR);
}

void WeatherMonitor::run(){
    _airParticiplesSensor->connect();
    _outdoorMeteoSensor->connect();

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
    _timer->interval(WEATHER_MONITOR_MEASUREMENT_DURATION_SECONDS);

    _airParticiplesSensor->beginMeasurement();
}

void WeatherMonitor::finishMeasuring(){
    _timer->interval(WEATHER_MONITOR_INTERVAL_SECONDS);
    WeatherMonitorData data;

    PmsData airParticiplesData = _airParticiplesSensor->endMeasurement();
    BME280Data outdoorMeteoData = _outdoorMeteoSensor->getData();

    data.isDataReceived = true;

    if(_onUpdateCallback != NULL) _onUpdateCallback(data);
}