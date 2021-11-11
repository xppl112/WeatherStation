#include <Arduino.h>
#include "UI/LEDIndicatorsController.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "Config.h"
extern GlobalSystemState* globalSystemState;

LEDIndicatorsController::LEDIndicatorsController(HardwareModulesRegistry* hardwareModulesRegistry){
    _pollutionRGBLed = new RGBLed(RGB_LED_R_PIN, RGB_LED_G_PIN, RGB_LED_B_PIN, true); 
    clearAllIndicators();
/*
    _timerSlow = new Ticker(1000, NULL, MILLIS); 
    _timerSlow->start();
    _timerFast = new Ticker(400, NULL, MILLIS); 
    _timerFast->start();*/
}

void LEDIndicatorsController::setPollutionLevel(WeatherMonitorData weatherData){
    if(!weatherData.isPMDataReceived) return;

    auto ledBrightness = globalSystemState->lightLevelPercent;
    _pollutionRGBLed->setBrightess(ledBrightness);
    
    int aqi = weatherData.calculateAQI();
    if(aqi >= (int)AQILevel::Good && aqi < (int)AQILevel::Moderate) _pollutionRGBLed->setColor(0, 255, 0);
    else if(aqi >= (int)AQILevel::Moderate && aqi < (int)AQILevel::UnhealthyForSensitiveGroups) _pollutionRGBLed->setColor(255, 127, 0);
    else if(aqi >= (int)AQILevel::UnhealthyForSensitiveGroups && aqi < (int)AQILevel::Unhealthy) _pollutionRGBLed->setColor(255, 32, 0);
    else if(aqi >= (int)AQILevel::Unhealthy && aqi < (int)AQILevel::VeryUnhealthy) _pollutionRGBLed->setColor(255, 0, 0);
    else if(aqi >= (int)AQILevel::VeryUnhealthy && aqi < (int)AQILevel::Hazardous) _pollutionRGBLed->setColor(255, 0, 16);
    else if(aqi >= (int)AQILevel::Hazardous) _pollutionRGBLed->setColor(120, 0, 255);
}

void LEDIndicatorsController::clearAllIndicators(){
    _pollutionRGBLed->setColor(0, 0, 0);
}

void LEDIndicatorsController::blinkBlue(){
    _pollutionRGBLed->setColor(0, 0, 255);
    delay(500);
    _pollutionRGBLed->setColor(0, 0, 0);
}