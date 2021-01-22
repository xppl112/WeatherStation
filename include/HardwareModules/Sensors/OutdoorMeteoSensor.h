#ifndef OutdoorMeteoSensor_H
#define OutdoorMeteoSensor_H

#include "HardwareModules/IHardwareModule.h"
#include "BME280Sensor.h"

class OutdoorMeteoSensor : public IHardwareModule
{
public:
    OutdoorMeteoSensor(uint8_t bme_i2c_address);
    void connect() override;
    void reset() override;
    bool isConnected() override { return _sensor->isConnected; }

    BME280Data getData();

private:
    BME280Sensor* _sensor;
};

#endif