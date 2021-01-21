#ifndef AirParticiplesSensor_H
#define AirParticiplesSensor_H

#include "HardwareModules/IHardwareModule.h"
#include "PlantowerSensor.h"

class AirParticiplesSensor : public IHardwareModule
{
public:
    AirParticiplesSensor();
    void connect() override;
    void beginMeasurement();
    PmsData endMeasurement();

    bool isConnected() override { return _sensor->isConnected; }
private:
    PlantowerSensor* _sensor;
};

#endif