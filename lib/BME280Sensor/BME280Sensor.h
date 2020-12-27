#include <stdint.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

class BME280Sensor
{
public:
  struct BME280Data {
    bool isDataReceived;

    float pressureInHPascals;
    float temperatureCelsium;
    float humidityPercent;
  };

  BME280Sensor(uint8_t i2c_address);

  bool connect(bool waitUntilConnected = false);
  BME280Data readData();

  bool isConnected;

private:
  Adafruit_BME280* _bme;
  uint8_t _i2c_address;
};