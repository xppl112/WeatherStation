#include "BME280Sensor.h"

BME280Sensor* bme;

  bme = new BME280Sensor(0x76);
  bme->connect();



 BME280Sensor::BME280Data data = bme->readData();