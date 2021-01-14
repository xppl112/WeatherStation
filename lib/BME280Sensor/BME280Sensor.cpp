#include <Arduino.h>
#include "BME280Sensor.h"

BME280Sensor::BME280Sensor(uint8_t i2c_address)
{
    _bme = new BME280<>;
    _i2c_address = i2c_address;    
    isConnected = false;
}

bool BME280Sensor::connect(bool waitUntilConnected){
    while (! _bme->begin(_i2c_address)){
        if(!waitUntilConnected) {
            isConnected = false;
            return false;
        }
    }
    isConnected = true;
    return true;    
}

BME280Data BME280Sensor::readData()
{
    BME280Data data { false };    

    if(this->isConnected) {
        _bme->refresh();

        data.isDataReceived = true;
        data.temperatureCelsium = _bme->temperature;
        data.humidityPercent = _bme->humidity;
        data.pressureInHPascals = _bme->pressure / 100.0F;
    }

    return data;
}