#ifndef OutdoorMeteoSensor_H
#define OutdoorMeteoSensor_H

#include "HardwareModules/IHardwareModule.h"

#include "BME280Sensor.h"
#define FAILED_MEASUREMENTS_TRESHOLD 2

class OutdoorMeteoSensor : public IHardwareModule
{
public:
    OutdoorMeteoSensor(uint8_t bme_i2c_address);
    HardwareModuleInfo getInfo() override {
        return HardwareModuleInfo {
            .Name = "BME280",
            .ConnectionType = HardwareModuleConnectionType::I2C,
            .PowerVoltage = 5,
            .CommunicationVoltage = 5,
            .MaxCurrent = 0
        };
    };
    void connect() override;
    void reset() override;
    bool isConnected() override { return _sensor->isConnected; }

    BME280Data getData();

private:
    BME280Sensor* _sensor;
    int _failedMeasurementsCount = 0;
};

#endif