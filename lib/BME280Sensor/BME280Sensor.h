#include <stdint.h>
#include <Wire.h>
#include <BME280_t.h>

struct BME280Data {
  bool isDataReceived;

  float pressureInHPascals;
  float temperatureCelsium;
  float humidityPercent;
};

class BME280Sensor
{
public:
  BME280Sensor(uint8_t i2c_address);

  bool connect(bool waitUntilConnected = false);
  BME280Data readData();

  bool isConnected;

private:
  BME280<>* _bme;
  uint8_t _i2c_address;
};