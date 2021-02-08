#include <Arduino.h>
#include <Wire.h>
#include "SystemUtils.h"
extern "C" {
    #include "user_interface.h"
}

void SystemUtils::printAllI2C(){
    byte error, address;
    int nDevices;
 
    Serial.println("Scanning...");
 
    nDevices = 0;
    for(address = 8; address < 127; address++ ){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
 
        if (error == 0){
            Serial.print("I2C device found at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.print(address,HEX);
            Serial.println(" !");
 
            nDevices++;
        }
        else if (error==4) {
            Serial.print("Unknow error at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.println(address,HEX);
        } 
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
}

bool SystemUtils::isI2CDeviceConnected(uint8_t address){
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0) return true;
    return false;
}

int SystemUtils::getFreeRAMBytes() {
    return ESP.getFreeHeap() / 1024;
}

int SystemUtils::getTotalRAMBytes() {
    return (float)ESP.getFlashChipSize() / 1024.0;
}

uint8_t SystemUtils::getCPUSpeedMHz() {
    return system_get_cpu_freq();
}