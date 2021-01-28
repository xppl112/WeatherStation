#include <stdint.h>
#include "DHT.h"

struct DHTData {
  bool isDataReceived;

  float temperatureCelsium;
  float humidityPercent;
};

class DHTSensor
{
public:
  DHTSensor(uint8_t dataPin);

  bool connect(bool connectionProbe = true);
  DHTData readData();

  bool isConnected;

private:
  DHT* _dht;
  uint8_t _dataPin;
};