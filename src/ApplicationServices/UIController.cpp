#include "ApplicationServices/UIController.h"


UIController::UIController(){
    _screen = new ScreenController();
    _ledIndicators = new LEDIndicatorsController();
    _inputsController = new InputsController();

    _screen->resetScreen();
    _screen->showSplashScreen();
}

void UIController::updateUI() {    
    updateInputs();
    
    _ledIndicators->updateSystemStatusLed();
}

void UIController::updateInputs() {
    ButtonPressed buttonPressed = _inputsController->updateInputs();

    switch(buttonPressed){
        case ButtonPressed::LEFT:
            flipScreenMode(false);
            showCurrentWeather();
            break;
        case ButtonPressed::RIGHT:
            flipScreenMode(true);
            showCurrentWeather();
            break;
    }
}

void UIController::onWeatherUpdated(WeatherMonitorData weatherMonitorData){
    _currentWeather = weatherMonitorData;
    showCurrentWeather();
}

void UIController::showCurrentWeather(){
    switch (_currentScreenMode){
        case ScreenMode::OFF: _screen->clearScreen();break;
        case ScreenMode::TEMPERATURE_OUTSIDE: _screen->showOutdoorTemperature(_currentWeather);break;
        case ScreenMode::AIR_POLLUTION: _screen->showAirPollution(_currentWeather);break;
        case ScreenMode::METEO_OUTSIDE: _screen->showOutdoorHumidityAndPressure(_currentWeather);break;
        case ScreenMode::METEO_INSIDE: _screen->showIndoorWeather(_currentWeather);break;
        case ScreenMode::AIR_QULITY: _screen->showAirQualityMeasurements(_currentWeather);break;
    }

    _ledIndicators->setPollutionLevel(_currentWeather);
    _ledIndicators->setWeatherStatusLed(_currentWeather);
}

void UIController::flipScreenMode(bool forward){
    int currentModeValue = (int)_currentScreenMode;
    if(forward) currentModeValue++;
    else currentModeValue--;

    if(currentModeValue > (int)ScreenMode::AIR_QULITY) currentModeValue = (int)ScreenMode::TEMPERATURE_OUTSIDE;
    if(currentModeValue < (int)ScreenMode::TEMPERATURE_OUTSIDE) currentModeValue = (int)ScreenMode::AIR_QULITY;

    _currentScreenMode = static_cast<ScreenMode>(currentModeValue);
}