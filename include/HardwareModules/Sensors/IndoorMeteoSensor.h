#ifndef IndoorMeteoSensor_H
#define IndoorMeteoSensor_H

#include "HardwareModules/IHardwareModule.h"
#include "DHTSensor.h"

class IndoorMeteoSensor : public IHardwareModule
{
public:
    IndoorMeteoSensor(uint8_t dhtSensorDataPin);
    void connect() override;
    void reset() override;
    bool isConnected() override { return _sensor->isConnected; }

    DHTData getData();

private:
    DHTSensor* _sensor;
};

#endif