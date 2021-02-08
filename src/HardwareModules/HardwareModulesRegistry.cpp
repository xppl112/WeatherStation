#include <Arduino.h>
#include "Config.h"
#include "HardwareModules/HardwareModulesRegistry.h"

HardwareModulesRegistry::HardwareModulesRegistry(){    
    mcpExtender = new MCPExtender(MCP_EXTENDER_I2C_ADDR);
    oledScreen = new OLED(OLED_I2C_ADDR);
    ledDisplay = new TM1637LED(TM1637_CLK_PIN, TM1637_DATA_PIN);
    airParticiplesSensor = new AirParticiplesSensor();
    outdoorMeteoSensor = new OutdoorMeteoSensor(BME_I2C_ADDR);
    indoorMeteoSensor = new IndoorMeteoSensor(DHT_DATA_PIN);

    hardwareModules[HardwareDeviceId::DEVICE_AIR_PARTICIPLES_SENSOR] = airParticiplesSensor;
    hardwareModules[HardwareDeviceId::DEVICE_OUTDOOR_METEO_SENSOR] = outdoorMeteoSensor;
    hardwareModules[HardwareDeviceId::DEVICE_INDOOR_METEO_SENSOR] = indoorMeteoSensor;
}

void HardwareModulesRegistry::reconnectAllDisconnectedDevices(bool onlyCritical){    
    if(!mcpExtender->isConnected) mcpExtender->connect();
    if(!oledScreen->isConnected) oledScreen->connect();
    if(!ledDisplay->isConnected) ledDisplay->connect();

    if(!onlyCritical){
        for (auto module : hardwareModules) {
            if(!module.second->isConnected())module.second->connect();
        }
    }
}

void HardwareModulesRegistry::resetDevice(HardwareDeviceId deviceId){
    hardwareModules[deviceId]->reset();
}

IHardwareModule* HardwareModulesRegistry::getDevice(HardwareDeviceId deviceId){
    return hardwareModules[deviceId];
}