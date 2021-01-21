#ifndef AirParticiplesSensor_H
#define AirParticiplesSensor_H

#include "PlantowerSensor.h"

class AirParticiplesSensor
{
public:
    AirParticiplesSensor();
    void connect();
    void beginMeasurement();
    PmsData endMeasurement();

    bool isConnected() {return _sensor->isConnected;}
private:
    PlantowerSensor* _sensor;
};

#endif