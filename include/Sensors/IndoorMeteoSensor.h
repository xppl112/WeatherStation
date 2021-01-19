#include "DHTSensor.h"

class IndoorMeteoSensor
{
public:
    IndoorMeteoSensor(uint8_t dhtSensorDataPin);
    void connect();
    DHTData getData();

private:
    DHTSensor* _sensor;
};