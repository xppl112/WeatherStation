#include "Integrations/BackendClient.h"
#include "GlobalObjects/GlobalSystemState.h"
extern GlobalSystemState* globalSystemState;

BackendClient::BackendClient(){
    _esp = new EspWifiClient();
}

unsigned long BackendClient::GetServerTime(){
    if(connectWifi()){
        HttpResponse response = _esp->sendGetRequest(
            _config.ServerHost, 
            _config.ServerApiGetTimeUrl);
        disconnectWifi();

        if(!response.success){
            return 0;
        }

        if(response.statusCode == 200){
            return std::stoul(response.payload.c_str(),nullptr,0);
        }
    }

    return 0;
}

SynchronizationDataResponse BackendClient::SynchronizeData(std::vector<WeatherMonitorData>* weatherDataCollection) {
    SynchronizationDataResponse returnResult = {.dataReceived = false };    
    if(weatherDataCollection->size() == 0) return returnResult;

    if(connectWifi()){
        //Send series of requests
        for(uint8_t requestN = 0; requestN < _config.RequestsSeriesMaxSize; requestN++){            
            //Send batch of reports in one request            
            if(weatherDataCollection->size() < _config.BatchMinSize)break;

            uint8_t reportN;
            String requestBody ="[";
            for(reportN = 0; reportN < _config.BatchMaxSize && reportN < weatherDataCollection->size(); reportN++){
                auto report = weatherDataCollection->at(reportN);
                requestBody+=report.toJson()+",";
            }
            requestBody+="]";

            if(reportN !=0){
                auto httpResponse = sendPostJsonRequest(_config.ServerHost, _config.ServerApiPostWeatherDataUrl,requestBody);
                if(httpResponse.success && httpResponse.statusCode == 200)
                {
                    weatherDataCollection->erase(weatherDataCollection->begin(), weatherDataCollection->begin() + reportN);
                    returnResult = SynchronizationDataResponse::constructFromJson(httpResponse.payload);
                }
            }
            yield();
        }
        
        disconnectWifi();
        return returnResult;
    }   
    return returnResult;
}

HttpResponse BackendClient::sendPostJsonRequest(const char* host, const char* resource, String jsonPayload){
    return _esp->sendPostJsonRequest(
        host, 
        resource,
        jsonPayload);
}

bool BackendClient::connectWifi(){
    bool isConnected = _esp->connectWifi(_config.WifiSSID, _config.WifiPassword);
    return isConnected;
}

void BackendClient::disconnectWifi(){
    _esp->disconnectWifi();
}