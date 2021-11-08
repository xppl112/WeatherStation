#include "HardwareModules/Sensors/LightSensor.h"
#include "Arduino.h"

LightSensor::LightSensor(uint8_t lightSensorPin){
    _lightSensorPin = lightSensorPin;
    pinMode(lightSensorPin, INPUT);
}

uint8_t LightSensor::getLightLevel(){
    auto analogValue = getDataFromAnalogPin(_lightSensorPin);
    return (uint8_t)(analogValue * 100 / 1024);
}

float LightSensor::getDataFromAnalogPin(uint8_t pin){
    float Vvalue=0.0;
    for(unsigned int i=0;i<30;i++){
        analogRead(pin); 
        delay(10);
    }    
    for(unsigned int i=0;i<256;i++){
        Vvalue=Vvalue+(float)analogRead(pin);
    }
    return Vvalue/256.0;
}