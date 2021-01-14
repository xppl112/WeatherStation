#include "Sensors/OutdoorMeteoSensor.h"

OutdoorMeteoSensor::OutdoorMeteoSensor(uint8_t bme_i2c_address){
    _sensor =  new BME280Sensor(bme_i2c_address);
}

void OutdoorMeteoSensor::connect(){
    _sensor->connect();
}

BME280Data OutdoorMeteoSensor::getData(){
    BME280Data data {.isDataReceived = false};

    if(!_sensor->isConnected)
        return data;//TODO: set healthcheck

     data = _sensor->readData();
     return data;
}