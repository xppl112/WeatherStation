#include "RGBLed.h"
#include "MCPExtender.h"

class LEDIndicatorsController
{
public:
    LEDIndicatorsController();
    void setPollutionLevel();
    void setStatusLed();

private:
    RGBLed* _pollutionRGBLed;
    MCPExtender* _mcp;
};