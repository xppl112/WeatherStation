 #include <stdint.h>
 #include <SoftwareSerial.h>
 #include "PMS.h"

class PlantowerSensor
{
public:
    struct PmsData {
        bool isDataReceived;
        // Atmospheric environment
        uint16_t PM_1_0;
        uint16_t PM_2_5;
        uint16_t PM_10_0;
    };

    PlantowerSensor(uint8_t rxPin, uint8_t txPin, uint8_t setPin);

    bool connect(bool waitUntilConnected = false);

    void sleep();
    void wakeUp();

    PmsData readData();
    PmsData readDataSyncronioslyAndSleep();

    bool isConnected;
    bool isInSleepMode;

private:
    uint8_t _rxPin;
    uint8_t _txPin;
    uint8_t _setPin;
    SoftwareSerial* _serial;
    PMS* _pms;
};