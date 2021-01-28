#ifndef IndoorMeteoSensor_H
#define IndoorMeteoSensor_H

#include "HardwareModules/IHardwareModule.h"
#include "DHTSensor.h"

#define FAILED_MEASUREMENTS_TRESHOLD 2

class IndoorMeteoSensor : public IHardwareModule
{
public:
    IndoorMeteoSensor(uint8_t dhtSensorDataPin);
    HardwareModuleInfo getInfo() override {
        return HardwareModuleInfo {
            .Name = "DHT11",
            .ConnectionType = HardwareModuleConnectionType::DIGITAL_PINS,
            .PowerVoltage = 3.3,
            .CommunicationVoltage = 3.3,
            .MaxCurrent = 0
        };
    };
    void connect() override;
    void reset() override;
    bool isConnected() override { return _sensor->isConnected; }

    DHTData getData();

private:
    DHTSensor* _sensor;
    int _failedMeasurementsCount = 0;
};

#endif