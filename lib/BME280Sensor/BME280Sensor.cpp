#include <Arduino.h>
#include "BME280Sensor.h"

BME280Sensor::BME280Sensor(uint8_t i2c_address)
{
    _bme = new Adafruit_BME280();
    _i2c_address = i2c_address;    
    isConnected = false;
}

bool BME280Sensor::connect(bool waitUntilConnected){
    while (! _bme->begin(_i2c_address, &Wire)){
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
        data.isDataReceived = true;
        data.temperatureCelsium = _bme->readTemperature();
        data.humidityPercent = _bme->readHumidity();
        data.pressureInHPascals = _bme->readPressure() / 100.0F;
    }

    return data;
}