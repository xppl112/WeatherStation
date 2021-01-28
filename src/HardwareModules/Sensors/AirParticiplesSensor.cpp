#include "HardwareModules/Sensors/AirParticiplesSensor.h"
#include "Arduino.h"

AirParticiplesSensor::AirParticiplesSensor(){
    _sensor = new PlantowerSensor();
}

void AirParticiplesSensor::connect(){
    _sensor->connect();
}

void AirParticiplesSensor::reset(){

}

void AirParticiplesSensor::beginMeasurement(){
    if(!_sensor->isConnected)
        return;

    _sensor->wakeUp();
}

PmsData AirParticiplesSensor::endMeasurement(){
    PmsData data = _sensor->readData();
    _sensor->sleep();

    // if we don't receive data for times, mark sensor as unconnected
     if(!data.isDataReceived){
         _failedMeasurementsCount++;
         if(_failedMeasurementsCount == FAILED_MEASUREMENTS_TRESHOLD) _sensor->isConnected = false;
     }
     else _failedMeasurementsCount = 0;

    return data;
}