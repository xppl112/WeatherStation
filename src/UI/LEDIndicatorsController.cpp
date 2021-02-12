#include <Arduino.h>
#include "UI/LEDIndicatorsController.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "Config.h"
extern GlobalSystemState* globalSystemState;

LEDIndicatorsController::LEDIndicatorsController(HardwareModulesRegistry* hardwareModulesRegistry){
    _mcp = hardwareModulesRegistry->mcpExtender;
    _pollutionRGBLed = new RGBLed(RGB_LED_R_PIN, RGB_LED_G_PIN, RGB_LED_B_PIN, false);
     
    _mcp->pinMode(LED_POWER, OUTPUT);
    _mcp->pinMode(LED_POWER_NIGHT, OUTPUT);
    _mcp->pinMode(LED_STATUS, OUTPUT);
    _mcp->pinMode(LED_DATA_TRANSFER, OUTPUT);_mcp->digitalWrite(LED_DATA_TRANSFER, LOW);
    _mcp->pinMode(LED_ERROR_STATUS, OUTPUT);_mcp->digitalWrite(LED_ERROR_STATUS, LOW);
    _mcp->pinMode(LED_TEMPERATURE, OUTPUT);_mcp->digitalWrite(LED_TEMPERATURE, LOW);
    _mcp->pinMode(LED_PRESSURE, OUTPUT);_mcp->digitalWrite(LED_PRESSURE, LOW);

    _pollutionRGBLed->setColor(0, 0, 0);

    _timerSlow = new Ticker(1000, NULL, MILLIS); 
    _timerSlow->start();
    _timerFast = new Ticker(400, NULL, MILLIS); 
    _timerFast->start();
}

void LEDIndicatorsController::setPollutionLevel(WeatherMonitorData weatherData){
    if(!weatherData.isPMDataReceived) return;
    
    int aqi = weatherData.calculateAQI();
    if(aqi >= (int)AQILevel::Good && aqi < (int)AQILevel::Moderate) _pollutionRGBLed->setColor(0, 255, 0);
    else if(aqi >= (int)AQILevel::Moderate && aqi < (int)AQILevel::UnhealthyForSensitiveGroups) _pollutionRGBLed->setColor(255, 255, 0);
    else if(aqi >= (int)AQILevel::UnhealthyForSensitiveGroups && aqi < (int)AQILevel::Unhealthy) _pollutionRGBLed->setColor(255, 127, 0);
    else if(aqi >= (int)AQILevel::Unhealthy && aqi < (int)AQILevel::VeryUnhealthy) _pollutionRGBLed->setColor(255, 0, 0);
    else if(aqi >= (int)AQILevel::VeryUnhealthy && aqi < (int)AQILevel::Hazardous) _pollutionRGBLed->setColor(144, 61, 152);
    else if(aqi >= (int)AQILevel::Hazardous) _pollutionRGBLed->setColor(127, 0, 30);
}

void LEDIndicatorsController::setWeatherStatusLed(WeatherMonitorData weatherData){    
    if(!weatherData.isOutsideMeteoDataReceived) return;

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

    auto ledPowerPin = LED_POWER;
    if(globalSystemState->isNightMode){
         ledPowerPin = LED_POWER_NIGHT;
        _mcp->digitalWrite(LED_POWER, LOW);
    }
    else _mcp->digitalWrite(LED_POWER_NIGHT, LOW);

    _mcp->digitalWrite(LED_DATA_TRANSFER, LOW);

    if(globalSystemState->systemHealth == HealthStatus::HEALTH_ERROR){            
            _mcp->digitalWrite(LED_STATUS, LOW);
            _mcp->digitalWrite(LED_ERROR_STATUS, _fastBlinkingLedOn);
    }
    else {
        switch(globalSystemState->powerStatus){
            case PowerStatus::Unknown:
            case PowerStatus::Regular:
                _mcp->digitalWrite(ledPowerPin, HIGH);break;
            case PowerStatus::Reserve:
            case PowerStatus::Warning:
                _mcp->digitalWrite(ledPowerPin, _slowBlinkingLedOn);break;
            case PowerStatus::DangerousVoltage:
                _mcp->digitalWrite(ledPowerPin, _fastBlinkingLedOn);break;
        }        

        if(globalSystemState->isNightMode){
            _mcp->digitalWrite(LED_STATUS, LOW);
            return;
        }

        if(globalSystemState->systemHealth == HealthStatus::HEALTH_WARNING && 
           globalSystemState->systemStatus != SystemStatus::DataTransfer){
                _mcp->digitalWrite(LED_STATUS, _fastBlinkingLedOn);
        }
        else {
            switch(globalSystemState->systemStatus){
                case SystemStatus::Unknown:
                case SystemStatus::Idle:
                    _mcp->digitalWrite(LED_STATUS, LOW);break;
                case SystemStatus::Measuring:
                    _mcp->digitalWrite(LED_STATUS, HIGH);break;
                case SystemStatus::DataTransfer:
                    _mcp->digitalWrite(LED_STATUS, LOW);
                    _mcp->digitalWrite(LED_DATA_TRANSFER, HIGH);
                    break;
            }
        }
    }
}

void LEDIndicatorsController::clearAllIndicators(){
    _mcp->digitalWrite(LED_TEMPERATURE, LOW);
    _mcp->digitalWrite(LED_PRESSURE, LOW);
    _pollutionRGBLed->setColor(0, 0, 0);
}