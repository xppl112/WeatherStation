#include "HardwareModules/Sensors/IndoorMeteoSensor.h"

IndoorMeteoSensor::IndoorMeteoSensor(uint8_t dhtSensorDataPin){
    _sensor =  new DHTSensor(dhtSensorDataPin);
}

void IndoorMeteoSensor::connect(){
    _sensor->connect();
}

void IndoorMeteoSensor::reset(){

}

DHTData IndoorMeteoSensor::getData(){
    DHTData data {.isDataReceived = false};

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