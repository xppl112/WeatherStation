#include "HardwareModules/Sensors/OutdoorMeteoSensor.h"

OutdoorMeteoSensor::OutdoorMeteoSensor(uint8_t bme_i2c_address){
    _sensor =  new BME280Sensor(bme_i2c_address);
}

void OutdoorMeteoSensor::connect(){
    _sensor->connect();
}

void OutdoorMeteoSensor::reset(){

}

BME280Data OutdoorMeteoSensor::getData(){
    BME280Data data {.isDataReceived = false};

    if(!_sensor->isConnected)
        return data;

     data = _sensor->readData();

    // if we don't receive data for times, mark sensor as unconnected
     if(!data.isDataReceived){
         _failedMeasurementsCount++;
         if(_failedMeasurementsCount == FAILED_MEASUREMENTS_TRESHOLD) _sensor->isConnected = false;
     }
     else _failedMeasurementsCount = 0;

     return data;
}