#ifndef SystemHealthReport_H
#define SystemHealthReport_H

#include <map>
#include <ArduinoJson.h>
#include <Healthchecks/HardwareDevicesHealthcheck.h> //TODO: get rid of tough coupling
#include <Healthchecks/NetworkingHealthcheck.h> //TODO: get rid of tough coupling
#include "GlobalObjects/GlobalSystemState.h"

struct SystemHealthReport {
    unsigned long timeStamp;
    HealthStatus systemHealth;
    std::vector<SystemError> systemErrors;
    
    PowerStatus powerStatus;
    float inputVoltage;

    std::map<String, HardwareDeviceStatus> hardwareDevices;
    NetworkingStatus networkingStatus;

    unsigned int freeRAM;
  
    String toJson(){
        DynamicJsonDocument doc(1024);

        doc["timeStamp"] = timeStamp;
        doc["systemHealth"] = (int)systemHealth;
        doc["freeRAM"] = freeRAM;

        JsonArray systemErrorsArray = doc.createNestedArray("systemErrors");
        for(auto error : systemErrors){
            JsonObject errorObject = systemErrorsArray.createNestedObject();
            errorObject["errorCode"] = (int)error.errorCode;
            errorObject["severity"] = (int)error.severity;
            errorObject["description"] = error.description;
        }

        doc["powerStatus"] = (int)powerStatus;
        doc["inputVoltage"] = inputVoltage;

        doc["networkingStatus"] = (int)networkingStatus;

        JsonArray hardwareDevicesArray = doc.createNestedArray("hardwareDevices");
        for(auto device : hardwareDevices){
            JsonObject deviceObject = hardwareDevicesArray.createNestedObject();
            deviceObject["name"] = device.first;
            deviceObject["status"] = (int)device.second;
        }

        String output;
        serializeJson(doc, output);
        doc.clear();
        doc.garbageCollect();

        return output;
    }
};

#endif