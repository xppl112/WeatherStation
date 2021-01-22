#ifndef HardwareModulesRegistry_H
#define HardwareModulesRegistry_H

#include <map>
#include "MCPExtender.h"
#include "OLED.h"
#include "HardwareModules/Sensors/AirParticiplesSensor.h"
#include "HardwareModules/Sensors/IndoorMeteoSensor.h"
#include "HardwareModules/Sensors/OutdoorMeteoSensor.h"

enum class HardwareDeviceId {
    DEVICE_MCP_EXTENDER, 
    DEVICE_OLED, 
    DEVICE_AIR_PARTICIPLES_SENSOR, 
    DEVICE_INDOOR_METEO_SENSOR, 
    DEVICE_OUTDOOR_METEO_SENSOR};

class HardwareModulesRegistry
{
public:
    HardwareModulesRegistry();
    void reconnectAllDevices();

    MCPExtender* mcpExtender;
    OLED* oledScreen;

    AirParticiplesSensor* airParticiplesSensor;
    IndoorMeteoSensor* indoorMeteoSensor;
    OutdoorMeteoSensor* outdoorMeteoSensor;
    
private:    
    std::map<HardwareDeviceId, IHardwareModule*> _hardwareModules;
};

#endif