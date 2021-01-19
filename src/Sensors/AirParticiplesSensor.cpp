#include "Sensors/AirParticiplesSensor.h"

AirParticiplesSensor::AirParticiplesSensor(uint8_t rxPin, uint8_t txPin){
    _sensor = new PlantowerSensor(rxPin, txPin);
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