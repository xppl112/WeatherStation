#ifndef AirParticiplesSensor_H
#define AirParticiplesSensor_H

#include "HardwareModules/IHardwareModule.h"
#include "PlantowerSensor.h"

class AirParticiplesSensor : public IHardwareModule
{
public:
    AirParticiplesSensor();
    void connect() override;
    void reset() override;
    bool isConnected() override { return _sensor->isConnected; }
    
    void beginMeasurement();
    PmsData endMeasurement();

private:
    PlantowerSensor* _sensor;
};

#endif