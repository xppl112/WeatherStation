#ifndef AirParticiplesSensor_H
#define AirParticiplesSensor_H

#include "HardwareModules/IHardwareModule.h"
#include "PlantowerSensor.h"

#define FAILED_MEASUREMENTS_TRESHOLD 2

class AirParticiplesSensor : public IHardwareModule
{
public:
    AirParticiplesSensor();
    HardwareModuleInfo getInfo() override {
        return HardwareModuleInfo {
            .Name = "PMS7003",
            .ConnectionType = HardwareModuleConnectionType::UART,
            .PowerVoltage = 5,
            .CommunicationVoltage = 3.3,
            .MaxCurrent = 100
        };
    };
    void connect() override;
    void reset() override;
    bool isConnected() override { return _sensor->isConnected; }
    
    void beginMeasurement();
    PmsData endMeasurement();

private:
    PlantowerSensor* _sensor;
    int _failedMeasurementsCount = 0;
};

#endif