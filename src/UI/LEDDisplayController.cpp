#include "UI/LEDDisplayController.h"

LEDDisplayController::LEDDisplayController(HardwareModulesRegistry* hardwareModulesRegistry){
    _display = hardwareModulesRegistry->ledDisplay;
}

void LEDDisplayController::clearScreen(){
    _display->clear();
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
    _display->printDecimalWithUnit(weatherData.PM2_5, '^');
}