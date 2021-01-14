#ifndef WEATHERMONITORDATA_H
#define WEATHERMONITORDATA_H

#define JSON_DELIMITER ';'
#define JSON_QUOTE '\"'
#define JSON_EQUAL '='

struct WeatherMonitorData {
    bool isDataReceived;
    long timeStampOfStart;
    long timeStampOfFinish;
    
    float temperatureOutside;
    int humidityOutside;
    float pressureOutside;

    float temperatureInside;
    int humidityInside;

    int PM1_0;
    int PM2_5;
    int PM_10_0;

    float TVOC;

    String serializeJson(){
        return String("{") + 
                JSON_QUOTE + "sD" + JSON_QUOTE + JSON_EQUAL + timeStampOfStart + JSON_DELIMITER + 
                JSON_QUOTE + "fD" + JSON_QUOTE + JSON_EQUAL + timeStampOfFinish + JSON_DELIMITER +
                JSON_QUOTE + "tO" + JSON_QUOTE + JSON_EQUAL + temperatureOutside + JSON_DELIMITER +
                JSON_QUOTE + "hO" + JSON_QUOTE + JSON_EQUAL + humidityOutside + JSON_DELIMITER +
                JSON_QUOTE + "pO" + JSON_QUOTE + JSON_EQUAL + pressureOutside + JSON_DELIMITER +
                JSON_QUOTE + "tI" + JSON_QUOTE + JSON_EQUAL + temperatureInside + JSON_DELIMITER +
                JSON_QUOTE + "hI" + JSON_QUOTE + JSON_EQUAL + humidityInside + JSON_DELIMITER +
                JSON_QUOTE + "P1" + JSON_QUOTE + JSON_EQUAL + PM1_0 + JSON_DELIMITER +
                JSON_QUOTE + "P2" + JSON_QUOTE + JSON_EQUAL + PM2_5 + JSON_DELIMITER +
                JSON_QUOTE + "P10" + JSON_QUOTE + JSON_EQUAL + PM_10_0 + JSON_DELIMITER +
                JSON_QUOTE + "TV" + JSON_QUOTE + JSON_EQUAL + TVOC + "}";
    }
};

#endif