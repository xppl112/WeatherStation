#include "Sensors/AirParticiplesSensor.h"
#include "Sensors/IndoorMeteoSensor.h"
#include "Sensors/OutdoorMeteoSensor.h"
#include "Sensors/TVOCSensor.h"

struct WeatherMonitorData {
    bool isDataReceived;
    
};

typedef void (*WeatherMonitorEventCallback)(WeatherMonitorData);

class WeatherMonitor
{
public:
    WeatherMonitor();
    int subscribeOnUpdate(WeatherMonitorEventCallback callback);
    enum WeatherMonitorState {IDLE, MEASURING};
    WeatherMonitorState state;

private:
    void startMeasuring();
    void finishMeasuring();

    WeatherMonitorEventCallback onUpdateCallbacks[];

    AirParticiplesSensor* airParticiplesSensor;
    IndoorMeteoSensor* indoorMeteoSensor;
    OutdoorMeteoSensor* outdoorMeteoSensor;
    TVOCSensor* tvocSensor;
};
