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
        return data;//TODO: set healthcheck

     data = _sensor->readData();
     return data;
}