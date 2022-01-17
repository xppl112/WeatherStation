#ifndef SynchronizationDataResponse_H
#define SynchronizationDataResponse_H

#include <ArduinoJson.h>

struct SynchronizationDataResponse {
    bool dataReceived;
    unsigned long timeStamp;
    bool isNightMode;

    static SynchronizationDataResponse constructFromJson(String json){
        SynchronizationDataResponse returnValue {.dataReceived = false};
        StaticJsonDocument<100> responseJson;
        deserializeJson(responseJson, json);

        if(responseJson.containsKey("ts")){
            returnValue.dataReceived = true;
            returnValue.timeStamp = responseJson["ts"];
            returnValue.isNightMode = responseJson["nm"];
        }
        return returnValue;
    }
};

#endif