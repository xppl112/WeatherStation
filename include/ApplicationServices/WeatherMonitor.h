#include "Sensors/AirParticiplesSensor.h"
#include "Sensors/IndoorMeteoSensor.h"
#include "Sensors/OutdoorMeteoSensor.h"
#include "Sensors/TVOCSensor.h"
#include "Models/WeatherMonitorData.h"
#include <Ticker.h>

typedef void (*WeatherMonitorUpdatedEventCallback)(WeatherMonitorData);

class WeatherMonitor
{
public:
    WeatherMonitor();
    void run();
    void updateTimers();
    void addUpdatedEventHandler(WeatherMonitorUpdatedEventCallback callback);
    void resetSensors();
    enum WeatherMonitorState {DISABLED, IDLE, MEASURING};
    WeatherMonitorState state = DISABLED;

private:
    void startMeasuring();
    void finishMeasuring();

    WeatherMonitorUpdatedEventCallback _onUpdateCallback;

    AirParticiplesSensor* _airParticiplesSensor;
    IndoorMeteoSensor* _indoorMeteoSensor;
    OutdoorMeteoSensor* _outdoorMeteoSensor;
    TVOCSensor* _tvocSensor;

    Ticker* _timer;
};
