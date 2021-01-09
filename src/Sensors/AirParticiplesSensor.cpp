#include "PlantowerSensor.h"

PlantowerSensor* plantower;

  plantower = new PlantowerSensor(8, 9, 7);
  plantower->connect();

  



   PlantowerSensor::PmsData pmsData = plantower->readDataSyncronioslyAndSleep();