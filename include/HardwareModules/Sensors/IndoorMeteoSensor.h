#ifndef IndoorMeteoSensor_H
#define IndoorMeteoSensor_H

#include "DHTSensor.h"

class IndoorMeteoSensor
{
public:
    IndoorMeteoSensor(uint8_t dhtSensorDataPin);
    void connect();
    DHTData getData();

    bool isConnected() {return _sensor->isConnected;}
private:
    DHTSensor* _sensor;
};

#endif