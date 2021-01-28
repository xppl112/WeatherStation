#include <Arduino.h>
#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t dataPin)
{
    _dht = new DHT(dataPin, DHT11);
    _dataPin = dataPin;    
    isConnected = false;
}

bool DHTSensor::connect(bool connectionProbe){
    _dht->begin();

    isConnected = true;
    if(connectionProbe && !readData().isDataReceived)isConnected = false;

    return isConnected;    
}

DHTData DHTSensor::readData()
{
    DHTData data { false };    

    if(this->isConnected) {
        data.isDataReceived = true;
        data.temperatureCelsium = _dht->readTemperature();
        data.humidityPercent = _dht->readHumidity();

        if(isnan(data.temperatureCelsium) || 
            data.temperatureCelsium < -100 ||
            data.temperatureCelsium > 200)data.isDataReceived = false;
    }

    return data;
}