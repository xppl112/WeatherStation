#ifndef HardwareModulesRegistry_H
#define HardwareModulesRegistry_H

#include <map>
#include "TM1637LED.h"
#include "HardwareModules/Sensors/AirParticiplesSensor.h"
#include "HardwareModules/Sensors/IndoorMeteoSensor.h"
#include "HardwareModules/Sensors/OutdoorMeteoSensor.h"
#include "HardwareModules/Sensors/LightSensor.h"

enum class HardwareDeviceId {
    DEVICE_LEDDISPLAY, 
    DEVICE_AIR_PARTICIPLES_SENSOR, 
    DEVICE_INDOOR_METEO_SENSOR, 
    DEVICE_OUTDOOR_METEO_SENSOR,
    DEVICE_LIGHT_SENSOR};

class HardwareModulesRegistry
{
public:
    HardwareModulesRegistry();
    void reconnectAllDisconnectedDevices(bool onlyCritical = false);
    void resetDevice(HardwareDeviceId deviceId);
    IHardwareModule* getDevice(HardwareDeviceId deviceId);

    TM1637LED* ledDisplay;

    AirParticiplesSensor* airParticiplesSensor;
    IndoorMeteoSensor* indoorMeteoSensor;
    OutdoorMeteoSensor* outdoorMeteoSensor;
    LightSensor* lightSensor;
    
    std::map<HardwareDeviceId, IHardwareModule*> hardwareModules;
};

#endif