#include <Arduino.h>
#include "Config.h"
#include "HardwareModules/HardwareModulesRegistry.h"

HardwareModulesRegistry::HardwareModulesRegistry(){    
    ledDisplay = new TM1637LED(TM1637_CLK_PIN, TM1637_DATA_PIN);
    airParticiplesSensor = new AirParticiplesSensor();
    outdoorMeteoSensor = new OutdoorMeteoSensor(BME_I2C_ADDR);
    indoorMeteoSensor = new IndoorMeteoSensor(DHT_DATA_PIN);
    lightSensor = new LightSensor(LIGHT_SENSOR_PIN);

    hardwareModules[HardwareDeviceId::DEVICE_AIR_PARTICIPLES_SENSOR] = airParticiplesSensor;
    hardwareModules[HardwareDeviceId::DEVICE_OUTDOOR_METEO_SENSOR] = outdoorMeteoSensor;
    hardwareModules[HardwareDeviceId::DEVICE_INDOOR_METEO_SENSOR] = indoorMeteoSensor;
    hardwareModules[HardwareDeviceId::DEVICE_LIGHT_SENSOR] = lightSensor;
}

void HardwareModulesRegistry::reconnectAllDisconnectedDevices(bool onlyCritical){    
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