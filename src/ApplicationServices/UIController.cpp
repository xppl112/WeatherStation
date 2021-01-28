#include "ApplicationServices/UIController.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

UIController::UIController(
    HardwareModulesRegistry* hardwareModulesRegistry, 
    HealthcheckController* healthcheckController)
{
    _screen = new ScreenController(hardwareModulesRegistry);
    _menuController = new MenuController(hardwareModulesRegistry, healthcheckController);
    _ledIndicators = new LEDIndicatorsController(hardwareModulesRegistry);
    _inputsController = new InputsController(hardwareModulesRegistry);

    _screen->showSplashScreen();
}

void UIController::updateUI() {    
    updateInputs();
    
    _ledIndicators->updateSystemStatusLed();
}

void UIController::updateInputs() {
    ButtonPressed buttonPressed = _inputsController->updateInputs();

    if(_isMenuMode){
        _menuController->buttonPressed(buttonPressed);
        if(!_menuController->isMenuActive()){
            disableMenuMode();
        }
    }
    else {
        switch(buttonPressed){
            case ButtonPressed::LEFT:
                flipScreenMode(false);
                showCurrentWeather();
                break;
            case ButtonPressed::RIGHT:
                flipScreenMode(true);
                showCurrentWeather();
                break;
            case ButtonPressed::UP:
                enableMenuMode();
                break;
            case ButtonPressed::DOWN:
                enableMenuMode();
                break;
            case ButtonPressed::LEFTRIGHT:
                enableMenuMode(true);
                break;
            case ButtonPressed::NONE:break;
        }
    }

    if(buttonPressed != ButtonPressed::NONE && globalSystemState->isNightMode){
        globalSystemState->isNightMode = false;        
        _currentScreenMode = ScreenMode::TEMPERATURE_OUTSIDE;
        showCurrentWeather();
    }
}

void UIController::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    _currentWeather = weatherMonitorData;
    showCurrentWeather();
}

void UIController::showCurrentWeather(){
    if(globalSystemState->isNightMode){
        _currentScreenMode = ScreenMode::OFF;
    }

    if(!_isMenuMode){        
        switch (_currentScreenMode){
            case ScreenMode::OFF: _screen->clearScreen();break;
            case ScreenMode::TEMPERATURE_OUTSIDE: _screen->showOutdoorTemperature(_currentWeather);break;
            case ScreenMode::AIR_POLLUTION: _screen->showAirPollution(_currentWeather);break;
            case ScreenMode::METEO_OUTSIDE: _screen->showOutdoorHumidityAndPressure(_currentWeather);break;
            case ScreenMode::METEO_INSIDE: _screen->showIndoorWeather(_currentWeather);break;
            case ScreenMode::AIR_QULITY: _screen->showAirQualityMeasurements(_currentWeather);break;
        }        
    }

    if(globalSystemState->isNightMode){
        _ledIndicators->clearAllIndicators();
    }
    else {
        _ledIndicators->setPollutionLevel(_currentWeather);
        _ledIndicators->setWeatherStatusLed(_currentWeather);
    }
}

void UIController::flipScreenMode(bool forward){
    int currentModeValue = (int)_currentScreenMode;
    if(forward) currentModeValue++;
    else currentModeValue--;

    if(currentModeValue > (int)ScreenMode::AIR_QULITY) currentModeValue = (int)ScreenMode::TEMPERATURE_OUTSIDE;
    if(currentModeValue < (int)ScreenMode::TEMPERATURE_OUTSIDE) currentModeValue = (int)ScreenMode::AIR_QULITY;

    _currentScreenMode = static_cast<ScreenMode>(currentModeValue);
}

void UIController::enableMenuMode(bool debugMode){
    _isMenuMode = true;
    _menuController->showMenu(!debugMode ? MAIN_MENU_MODE : DEBUG_MENU_MODE);
}

void UIController::disableMenuMode(){
    _isMenuMode = false;
    showCurrentWeather();
}