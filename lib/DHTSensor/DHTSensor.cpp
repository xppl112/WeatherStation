#include <Arduino.h>
#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t dataPin)
{
    _dht = new DHT(dataPin, DHT11);
    _dataPin = dataPin;    
    isConnected = false;
}

bool DHTSensor::connect(bool waitUntilConnected){
    _dht->begin();
    isConnected = true;
    return isConnected;    
}

DHTData DHTSensor::readData()
{
    DHTData data { false };    

    if(this->isConnected) {
        data.isDataReceived = true;
        data.temperatureCelsium = _dht->readTemperature();
        data.humidityPercent = _dht->readHumidity();
    }

    return data;
}