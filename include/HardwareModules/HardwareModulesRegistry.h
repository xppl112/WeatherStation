#ifndef HardwareModulesRegistry_H
#define HardwareModulesRegistry_H

#include "MCPExtender.h"
#include "OLED.h"
#include "HardwareModules/Sensors/AirParticiplesSensor.h"
#include "HardwareModules/Sensors/IndoorMeteoSensor.h"
#include "HardwareModules/Sensors/OutdoorMeteoSensor.h"

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

};

#endif