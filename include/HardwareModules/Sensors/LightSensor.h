#ifndef LightSensor_H
#define LightSensor_H

#include "HardwareModules/IHardwareModule.h"
#include <stdint.h>

class LightSensor : public IHardwareModule
{
public:
    LightSensor(uint8_t lightSensorPin);
    HardwareModuleInfo getInfo() override {
        return HardwareModuleInfo {
            .Name = "LightResistor",
            .ConnectionType = HardwareModuleConnectionType::ANALOG_PINS,
            .PowerVoltage = 3.3,
            .CommunicationVoltage = 3.3,
            .MaxCurrent = 0
        };
    };
    void connect() override {}
    void reset() override {}
    bool isConnected() override { return true; }
    
    uint8_t getLightLevel();

private:
    uint8_t _lightSensorPin;
    float getDataFromAnalogPin(uint8_t pin);
};

#endif