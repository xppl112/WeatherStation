#ifndef WEATHERMONITORDATA_H
#define WEATHERMONITORDATA_H

#include <ArduinoJson.h>

enum class AQILevel {
    Good = 0,
    Moderate = 51,
    UnhealthyForSensitiveGroups = 101,
    Unhealthy = 151, 
    VeryUnhealthy = 201,
    Hazardous = 300
};

enum class PressureLevel {
    Low = 1000,
    Normal = 1013,
    High = 1030
};

struct WeatherMonitorData {
    long timeStampOfStart;
    long timeStampOfFinish;
    
    bool isOutsideMeteoDataReceived;
    int humidityOutside = 0;
    float temperatureOutside = 0;
    float pressureOutside = 0;

    bool isInsideMeteoDataReceived;
    float temperatureInside = 0;
    int humidityInside = 0;

    bool isPMDataReceived;
    int PM1_0 = 0;
    int PM2_5 = 0; //µg/m3
    int PM_10_0 = 0;

    float TVOC;
    float H2CO;
    float NO2;

    // AQI (US)
    int calculateAQI(){
        int AQI = 0;

        if(isPMDataReceived){
            if(PM2_5 >= 0 && PM2_5 < 12) AQI = PM2_5 * 50 / 12;
            else if(PM2_5 >= 12 && PM2_5 < 35) AQI = PM2_5 * 100 / 35;
            else if(PM2_5 >= 35 && PM2_5 < 55) AQI = PM2_5 * 150 / 55;
            else if(PM2_5 >= 55 && PM2_5 < 150) AQI = PM2_5 * 200 / 150;
            else if(PM2_5 >= 150 && PM2_5 < 250) AQI = PM2_5 * 300 / 250;
            else if(PM2_5 >= 250 && PM2_5 < 350) AQI = PM2_5 * 400 / 350;
            else if(PM2_5 >= 350) AQI = PM2_5 * 500 / 500;
        }

        return AQI;
    }

    PressureLevel getPressureLevel(){
        if(pressureOutside <= (int)PressureLevel::Low) return PressureLevel::Low;
        if(pressureOutside >= (int)PressureLevel::High) return PressureLevel::High;
        return PressureLevel::Normal;
    }

    String toJson(){
        DynamicJsonDocument doc(2048);

        doc["tss"] = timeStampOfStart;
        doc["tsf"] = timeStampOfFinish;

        if(isOutsideMeteoDataReceived){
            doc["to"] = temperatureOutside;
            doc["ho"] = humidityOutside;
            doc["po"] = pressureOutside;
        }
        if(isInsideMeteoDataReceived){
            doc["ti"] = temperatureInside;
            doc["hi"] = humidityInside;
        }
        if(isPMDataReceived){
            doc["p1"] = PM1_0;
            doc["p2"] = PM2_5;
            doc["p10"] = PM_10_0;
        }

        String output;
        serializeJson(doc, output);
        doc.clear();
        doc.garbageCollect();

        return output;
    }
};

#endif