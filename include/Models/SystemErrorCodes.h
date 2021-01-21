#ifndef SYSTEM_ERROR_CODES_H
#define SYSTEM_ERROR_CODES_H

enum class SystemErrorSeverity { SystemError, SystemWarning};

enum class SystemErrorCode {
    Unknown = 0, 
    OLED_I2CConnectionFailure = 10, 
    MCPExtender_I2CConnectionFailure = 11,

    PlantowerSensor_UARTConnectionFailure = 20, 
    PlantowerSensor_DataReceivingFailure = 21,
    BME280Sensor_I2CConnectionFailure = 22, 
    DHTSensor_ConnectionFailure = 23, 

    Network_WifiConnectionFailure = 30,
    Network_BackendServerConnectionFailure = 31,
    Network_BackendServerInternalError = 32
};

#endif