#include "HardwareModules/Sensors/AirParticiplesSensor.h"

AirParticiplesSensor::AirParticiplesSensor(){
    _sensor = new PlantowerSensor();
}

void AirParticiplesSensor::connect(){
    _sensor->connect();
}

void AirParticiplesSensor::beginMeasurement(){
    if(!_sensor->isConnected)
        return;//TODO: return error

    _sensor->wakeUp();
}

PmsData AirParticiplesSensor::endMeasurement(){
    PmsData data = _sensor->readData();
    _sensor->sleep();

    return data;
}