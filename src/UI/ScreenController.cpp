#include "UI/ScreenController.h"
#include "StringUtils.h"

ScreenController::ScreenController(HardwareModulesRegistry* hardwareModulesRegistry){
    _oled = hardwareModulesRegistry->oledScreen;
}

void ScreenController::clearScreen(){
    _oled->clear();
    _oled->render();
}

void ScreenController::showSplashScreen(){
    _oled->setWordWrapMode(false);
    _oled->clear();
    _oled->setCursor(30,9);_oled->print("Weather", OLEDFont::FONT_SMALL);
    _oled->setCursor(35,25);_oled->print("station", OLEDFont::FONT_SMALL);
    _oled->setCursor(45,50);_oled->print("LOADING...", OLEDFont::FONT_SMALLEST);
    _oled->render();
}

void ScreenController::showIndoorWeather(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,11);
    _oled->print("Indoor weather", OLEDFont::FONT_TITLE);

    _oled->setCursor(0,30);
    _oled->print("temp: " + StringUtils::floatToString(weatherData.temperatureInside) + "`C", OLEDFont::FONT_SMALL);
    _oled->setCursor(0,45);
    _oled->print("hum:  " + String(weatherData.humidityInside) + " %", OLEDFont::FONT_SMALL);
    _oled->render();
}

void ScreenController::showOutdoorTemperature(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,12);
    _oled->print("Outdoor temp", OLEDFont::FONT_TITLE);

    _oled->setCursor(0,55);
    _oled->print(StringUtils::floatToString(weatherData.temperatureOutside) + "`C", OLEDFont::FONT_BODY_BIG);
    _oled->render();
}

void ScreenController::showOutdoorHumidityAndPressure(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,12);
    _oled->print("Outdoor weather", OLEDFont::FONT_TITLE);

    _oled->setCursor(0,30);
    _oled->print("temp: " + StringUtils::floatToString(weatherData.temperatureOutside) + "`C", OLEDFont::FONT_SMALL);
    _oled->setCursor(0,45);
    _oled->print("hum:  " + String(weatherData.humidityOutside) + " %", OLEDFont::FONT_SMALL);
    _oled->setCursor(0,60);
    _oled->print("press: " + StringUtils::floatToString(weatherData.pressureOutside) + " hPa", OLEDFont::FONT_SMALL);
    _oled->render();
}

void ScreenController::showAirQualityMeasurements(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,12);
    _oled->print("PM 2.5", OLEDFont::FONT_TITLE);

    _oled->setCursor(0,55);
    _oled->print(String(weatherData.PM2_5), OLEDFont::FONT_BODY_BIG);
    _oled->render();
}

void ScreenController::showAirPollution(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,11);
    _oled->print("Air pollution AQI", OLEDFont::FONT_TITLE);

    _oled->setCursor(0,55);
    _oled->print(String(weatherData.calculateAQI()), OLEDFont::FONT_BODY_BIG);

    _oled->render();
}