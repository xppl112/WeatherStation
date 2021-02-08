#ifndef HardwareModulesRegistry_H
#define HardwareModulesRegistry_H

#include <map>
#include "MCPExtender.h"
#include "OLED.h"
#include "TM1637LED.h"
#include "HardwareModules/Sensors/AirParticiplesSensor.h"
#include "HardwareModules/Sensors/IndoorMeteoSensor.h"
#include "HardwareModules/Sensors/OutdoorMeteoSensor.h"

enum class HardwareDeviceId {
    DEVICE_MCP_EXTENDER, 
    DEVICE_OLED, 
    DEVICE_LEDDISPLAY, 
    DEVICE_AIR_PARTICIPLES_SENSOR, 
    DEVICE_INDOOR_METEO_SENSOR, 
    DEVICE_OUTDOOR_METEO_SENSOR};

class HardwareModulesRegistry
{
public:
    HardwareModulesRegistry();
    void reconnectAllDisconnectedDevices(bool onlyCritical = false);
    void resetDevice(HardwareDeviceId deviceId);
    IHardwareModule* getDevice(HardwareDeviceId deviceId);

    MCPExtender* mcpExtender;
    OLED* oledScreen;
    TM1637LED* ledDisplay;

    AirParticiplesSensor* airParticiplesSensor;
    IndoorMeteoSensor* indoorMeteoSensor;
    OutdoorMeteoSensor* outdoorMeteoSensor;
    
    std::map<HardwareDeviceId, IHardwareModule*> hardwareModules;
};

#endif