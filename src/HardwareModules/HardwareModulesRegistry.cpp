#include <Arduino.h>
#include "Config.h"
#include "HardwareModules/HardwareModulesRegistry.h"

HardwareModulesRegistry::HardwareModulesRegistry(){    
    mcpExtender = new MCPExtender(MCP_EXTENDER_I2C_ADDR);
    oledScreen = new OLED(OLED_I2C_ADDR);
    airParticiplesSensor = new AirParticiplesSensor();
    outdoorMeteoSensor = new OutdoorMeteoSensor(BME_I2C_ADDR);
    indoorMeteoSensor = new IndoorMeteoSensor(DHT_DATA_PIN);

    /*_hardwareModules[HardwareDeviceId::DEVICE_MCP_EXTENDER] = mcpExtender;
    _hardwareModules[HardwareDeviceId::DEVICE_OLED] = oledScreen;*/
    _hardwareModules[HardwareDeviceId::DEVICE_AIR_PARTICIPLES_SENSOR] = airParticiplesSensor;
    _hardwareModules[HardwareDeviceId::DEVICE_OUTDOOR_METEO_SENSOR] = outdoorMeteoSensor;
    _hardwareModules[HardwareDeviceId::DEVICE_INDOOR_METEO_SENSOR] = indoorMeteoSensor;
}

void HardwareModulesRegistry::reconnectAllDevices(){    
    if(!mcpExtender->isConnected) mcpExtender->connect();
    if(!oledScreen->isConnected) oledScreen->connect();

    for (auto module : _hardwareModules) {
        if(!module.second->isConnected())module.second->connect();
    }
}