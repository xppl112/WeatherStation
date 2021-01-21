#ifndef OutdoorMeteoSensor_H
#define OutdoorMeteoSensor_H

#include "BME280Sensor.h"

class OutdoorMeteoSensor
{
public:
    OutdoorMeteoSensor(uint8_t bme_i2c_address);
    void connect();
    BME280Data getData();

    bool isConnected() {return _sensor->isConnected;}
private:
    BME280Sensor* _sensor;
};

#endif