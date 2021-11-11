#include "UI/LEDDisplayController.h"

LEDDisplayController::LEDDisplayController(HardwareModulesRegistry* hardwareModulesRegistry){
    _display = hardwareModulesRegistry->ledDisplay;
}

void LEDDisplayController::clearScreen(){
    _display->clear();
}

void LEDDisplayController::setBrightness(uint8_t brightnessLevelPercent){
    if(brightnessLevelPercent < 10) brightnessLevelPercent = 10;
    if(_displayBrightnessLevelPercent != brightnessLevelPercent){
        _displayBrightnessLevelPercent = brightnessLevelPercent;
        _display->setBrightness(brightnessLevelPercent);
    }
}

void LEDDisplayController::showOutdoorTemperature(WeatherMonitorData weatherData){
    _display->printDecimalWithUnit(weatherData.temperatureOutside, 'c');
}

void LEDDisplayController::showOutdoorHumidity(WeatherMonitorData weatherData){
    _display->printDecimalWithUnit(weatherData.humidityOutside, '%');
}

void LEDDisplayController::showIndoorTemperature(WeatherMonitorData weatherData){
    _display->printDecimalWithUnit(weatherData.temperatureInside, '_');
}

void LEDDisplayController::showAirPollution(WeatherMonitorData weatherData){
    _display->printIntWithUnit(weatherData.PM2_5, '^');
}