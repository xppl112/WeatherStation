#include "BME280Sensor.h"

class OutdoorMeteoSensor
{
public:
    OutdoorMeteoSensor(uint8_t bme_i2c_address);
    void connect();
    BME280Data getData();

private:
    BME280Sensor* _sensor;
};