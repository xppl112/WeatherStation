//#include "LCD.h"
#include "OLED.h"

class ScreenController
{
public:
    ScreenController();
    void resetScreen();
    void showWeather();

private:
    //LCD* lcd;
    OLED* _oled;

};