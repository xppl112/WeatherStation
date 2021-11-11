#include "ApplicationServices/UIController.h"
#include "GlobalObjects/GlobalSystemState.h"
#include "Config.h"
extern GlobalSystemState* globalSystemState;

UIController::UIController(HardwareModulesRegistry* hardwareModulesRegistry)
{
    _ledDisplayController = new LEDDisplayController(hardwareModulesRegistry);
    _ledIndicators = new LEDIndicatorsController(hardwareModulesRegistry);
    _inputsController = new InputsController(hardwareModulesRegistry);
}

void UIController::updateUI() {
    redrawUI(); 
    updateInputs();    
}

void UIController::updateInputs() {
    ButtonPressed buttonPressed = _inputsController->updateInputs();

    if(buttonPressed == ButtonPressed::TOUCH){
        int currentModeValue = (int)_currentLedDisplayMode;
        currentModeValue++;
        if(currentModeValue > (int)LedDisplayMode::AIR_POLLUTION) currentModeValue = (int)LedDisplayMode::OFF;
        _currentLedDisplayMode = static_cast<LedDisplayMode>(currentModeValue);
        redrawUI();   
    }    
}

void UIController::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    _currentWeather = weatherMonitorData;
    redrawUI();
}

void UIController::redrawUI(){
    _ledIndicators->setPollutionLevel(_currentWeather);
    
    _ledDisplayController->setBrightness(globalSystemState->lightLevelPercent);
  
    switch (_currentLedDisplayMode){
        case LedDisplayMode::OFF: _ledDisplayController->clearScreen();break;
        case LedDisplayMode::TEMPERATURE_OUTSIDE: _ledDisplayController->showOutdoorTemperature(_currentWeather);break;
        case LedDisplayMode::HUMIDITY_OUTSIDE: _ledDisplayController->showOutdoorHumidity(_currentWeather);break;
        case LedDisplayMode::TEMPERATURE_INSIDE: _ledDisplayController->showIndoorTemperature(_currentWeather);break;
        case LedDisplayMode::AIR_POLLUTION: _ledDisplayController->showAirPollution(_currentWeather);break;
    }   
}