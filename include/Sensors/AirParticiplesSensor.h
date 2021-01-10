#include "PlantowerSensor.h"

class AirParticiplesSensor
{
public:
    AirParticiplesSensor(uint8_t rxPin, uint8_t txPin);
    void connect();
    void beginMeasurement();
    PmsData endMeasurement();

private:
    PlantowerSensor* _sensor;
};