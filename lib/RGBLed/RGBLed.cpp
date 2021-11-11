#include <Arduino.h>
#include "RGBLed.h"

RGBLed::RGBLed(uint8_t pinR, uint8_t pinG, uint8_t pinB, bool commonAnode){
    _pinR = pinR;
    _pinG = pinG;
    _pinB = pinB;
    _commonAnode = commonAnode;

    pinMode(_pinR, OUTPUT);
    pinMode(_pinG, OUTPUT);
    pinMode(_pinB, OUTPUT);
}

void RGBLed::setBrightess(uint8_t brightnessPercent){
    _brightnessPercent = brightnessPercent;
}

void RGBLed::setColor(uint8_t R, uint8_t G, uint8_t B){
    R = R * PWMRANGE / 255;
    G = G * PWMRANGE / 255;
    B = B * PWMRANGE / 255;

    // Brightness adjusting
    R = (float)R * ((float)_brightnessPercent / 100.0);
    G = (float)G * ((float)_brightnessPercent / 100.0);
    B = (float)B * ((float)_brightnessPercent / 100.0);

    if(_commonAnode){
        analogWrite(_pinR, R);
        analogWrite(_pinG, G);
        analogWrite(_pinB, B);
    }
    else {
        analogWrite(_pinR, PWMRANGE - R);
        analogWrite(_pinG, PWMRANGE - G);
        analogWrite(_pinB, PWMRANGE - B);
    }
}