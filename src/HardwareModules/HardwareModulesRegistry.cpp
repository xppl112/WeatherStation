#include <Arduino.h>
#include "Config.h"
#include "HardwareModules/HardwareModulesRegistry.h"

HardwareModulesRegistry::HardwareModulesRegistry(){    
    mcpExtender = new MCPExtender(MCP_EXTENDER_I2C_ADDR);
    oledScreen = new OLED(OLED_I2C_ADDR);
    airParticiplesSensor = new AirParticiplesSensor();
    outdoorMeteoSensor = new OutdoorMeteoSensor(BME_I2C_ADDR);
    indoorMeteoSensor = new IndoorMeteoSensor(DHT_DATA_PIN);
}

void HardwareModulesRegistry::reconnectAllDevices(){    
    if(!mcpExtender->isConnected)mcpExtender->connect();
    if(!oledScreen->isConnected)oledScreen->connect();
    if(!airParticiplesSensor->isConnected())airParticiplesSensor->connect();
    if(!outdoorMeteoSensor->isConnected())outdoorMeteoSensor->connect();
    if(!indoorMeteoSensor->isConnected())indoorMeteoSensor->connect();
}