#include "UI/ScreenController.h"
#include "StringUtils.h"
#include "Config.h"

ScreenController::ScreenController(){
    _oled = new OLED(OLED_I2C_ADDR);
}

void ScreenController::resetScreen(){
    _oled->connect();
    clearScreen();
}

void ScreenController::clearScreen(){
    _oled->clear();
    _oled->render();
}

void ScreenController::showSplashScreen(){
    _oled->setWordWrapMode(false);
    _oled->clear();
    _oled->setCursor(30,9);_oled->print("Weather", FONT_SMALL);
    _oled->setCursor(35,25);_oled->print("station", FONT_SMALL);
    _oled->setCursor(10,50);_oled->print("measuring...", FONT_SMALL);
    _oled->render();
}

void ScreenController::showIndoorWeather(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,11);
    _oled->print("Indoor weather", FONT_TITLE);

    _oled->setCursor(0,30);
    _oled->print("temp: " + StringUtils::floatToString(weatherData.temperatureInside) + "`C", FONT_SMALL);
    _oled->setCursor(0,45);
    _oled->print("hum:  " + String(weatherData.humidityInside) + " %", FONT_SMALL);
    _oled->render();
}

void ScreenController::showOutdoorTemperature(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,12);
    _oled->print("Outdoor temp", FONT_TITLE);

    _oled->setCursor(0,55);
    _oled->print(StringUtils::floatToString(weatherData.temperatureOutside) + "`C", FONT_BODY_BIG);
    _oled->render();
}

void ScreenController::showOutdoorHumidityAndPressure(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,12);
    _oled->print("Outdoor weather", FONT_TITLE);

    _oled->setCursor(0,30);
    _oled->print("temp: " + StringUtils::floatToString(weatherData.temperatureOutside) + "`C", FONT_SMALL);
    _oled->setCursor(0,45);
    _oled->print("hum:  " + String(weatherData.humidityOutside) + " %", FONT_SMALL);
    _oled->setCursor(0,60);
    _oled->print("press: " + StringUtils::floatToString(weatherData.pressureOutside) + " hPa", FONT_SMALL);
    _oled->render();
}

void ScreenController::showAirQualityMeasurements(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,12);
    _oled->print("PM 2.5", FONT_TITLE);

    _oled->setCursor(0,55);
    _oled->print(String(weatherData.PM2_5), FONT_BODY_BIG);
    _oled->render();
}

void ScreenController::showAirPollution(WeatherMonitorData weatherData){
    _oled->setWordWrapMode(false);
    _oled->clear();

    _oled->setCursor(0,11);
    _oled->print("Air pollution AQI", FONT_TITLE);

    _oled->setCursor(0,55);
    _oled->print(String(weatherData.calculateAQI()), FONT_BODY_BIG);

    _oled->render();
}