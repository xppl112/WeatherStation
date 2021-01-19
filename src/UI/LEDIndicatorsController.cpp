#include <Arduino.h>
#include "UI/LEDIndicatorsController.h"
#include "GlobalObjects/GlobalDevices.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "Config.h"
extern GlobalDevices* globalDevices;
extern GlobalSystemState* globalSystemState;

LEDIndicatorsController::LEDIndicatorsController(){
    _pollutionRGBLed = new RGBLed(RGB_LED_R_PIN, RGB_LED_G_PIN, RGB_LED_B_PIN, false);
    
    _mcp = globalDevices->mcpExtender;    
    _mcp->pinMode(LED_POWER, OUTPUT);
    _mcp->pinMode(LED_TEMPERATURE, OUTPUT);
    _mcp->pinMode(LED_STATUS, OUTPUT);
    _mcp->pinMode(LED_PRESSURE, OUTPUT);
    _mcp->pinMode(LED_RESERVED, OUTPUT);

    _pollutionRGBLed->setColor(0, 0, 0);

    _timerSlow = new Ticker(1000, NULL, MILLIS); 
    _timerSlow->start();
    _timerFast = new Ticker(400, NULL, MILLIS); 
    _timerFast->start();
}

void LEDIndicatorsController::setPollutionLevel(WeatherMonitorData weatherData){
    int aqi = weatherData.calculateAQI();
    if(aqi >= AQILevel::Good && aqi < AQILevel::Moderate) _pollutionRGBLed->setColor(0, 255, 0);
    else if(aqi >= AQILevel::Moderate && aqi < AQILevel::UnhealthyForSensitiveGroups) _pollutionRGBLed->setColor(255, 255, 0);
    else if(aqi >= AQILevel::UnhealthyForSensitiveGroups && aqi < AQILevel::Unhealthy) _pollutionRGBLed->setColor(255, 127, 0);
    else if(aqi >= AQILevel::Unhealthy && aqi < AQILevel::VeryUnhealthy) _pollutionRGBLed->setColor(255, 0, 0);
    else if(aqi >= AQILevel::VeryUnhealthy && aqi < AQILevel::Hazardous) _pollutionRGBLed->setColor(144, 61, 152);
    else if(aqi >= AQILevel::Hazardous) _pollutionRGBLed->setColor(127, 0, 30);
}

void LEDIndicatorsController::setWeatherStatusLed(WeatherMonitorData weatherData){    
    _mcp->digitalWrite(LED_TEMPERATURE, weatherData.temperatureOutside <= 0);
    _mcp->digitalWrite(LED_PRESSURE, weatherData.getPressureLevel() != PressureLevel::Normal);
}

void LEDIndicatorsController::updateSystemStatusLed(){
    _timerSlow->update();
    _timerFast->update();
    if(_timerSlow->state() == FIRED){
        _slowBlinkingLedOn = !_slowBlinkingLedOn;
        _timerSlow->resetStatus();
    }
    if(_timerFast->state() == FIRED){
        _fastBlinkingLedOn = !_fastBlinkingLedOn;
        _timerFast->resetStatus();
    }

    switch(globalSystemState->powerStatus){
        case GlobalSystemState::PowerStatus::Regular:
            _mcp->digitalWrite(LED_POWER, HIGH);break;
        case GlobalSystemState::PowerStatus::Reserve:
            _mcp->digitalWrite(LED_POWER, _slowBlinkingLedOn);break;
        case GlobalSystemState::PowerStatus::Warning:
            _mcp->digitalWrite(LED_POWER, _fastBlinkingLedOn);break;
    }

    switch(globalSystemState->systemStatus){
        case GlobalSystemState::SystemStatus::Idle:
            _mcp->digitalWrite(LED_STATUS, LOW);break;
        case GlobalSystemState::SystemStatus::Measuring:
            _mcp->digitalWrite(LED_STATUS, HIGH);break;
        case GlobalSystemState::SystemStatus::DataTransfer:
            _mcp->digitalWrite(LED_STATUS, _slowBlinkingLedOn);break;
        case GlobalSystemState::SystemStatus::SystemWarning:
            _mcp->digitalWrite(LED_STATUS, _fastBlinkingLedOn);break;
        case GlobalSystemState::SystemStatus::FatalFailure:
            _mcp->digitalWrite(LED_POWER, _fastBlinkingLedOn);
            _mcp->digitalWrite(LED_STATUS, _fastBlinkingLedOn);break;
    }

}