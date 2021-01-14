//#include "SoftwareSerial.h"
#include "EspWifiClient.h"
#include "WiFiEspClient.h"
#include "WiFiEsp.h"
#include "HttpClient.h"

#define JSON_CONTENT_TYPE "application/json"

EspWifiClient::EspWifiClient(uint8_t pinRx, uint8_t pinTx){
    _pinRx = pinRx;
    _pinTx = pinTx;

    _wifiStatus = WL_IDLE_STATUS;
    isEspReady = false;
    isWifiConnected = false;
}

EspWifiClient::EspWifiClient(Stream* stream){
    _espSerial = stream;
}

bool EspWifiClient::initEsp(bool waitUntilConnected) {
 /*   if(!_espSerial){
        _espSerial = new SoftwareSerial(_pinRx, _pinTx);
    }*/

    _esp = new WiFiEspClient();
    WiFi.init(_espSerial);

    uint8_t status =  WiFi.status();
    if(status == WL_NO_SHIELD) {
        isEspReady = false;
    }
    else isEspReady = true;

    return isEspReady;
}

bool EspWifiClient::connectWifi(const char* ssid, const char* password, uint8_t timeoutSeconds){
    _wifiSsid = ssid;
    _wifiPassword = password;
    isWifiConnected = false;

    uint8_t secondsElapsed = 0;
    while ( _wifiStatus != WL_CONNECTED) {
        _wifiStatus = WiFi.begin(ssid, password);
        if( _wifiStatus == WL_CONNECTED) break;

        secondsElapsed++;
        if(secondsElapsed >= timeoutSeconds) return false;
        delay(1000);
    }

    isWifiConnected = true;
    return isWifiConnected;
}

void EspWifiClient::disconnectWifi() {
    _wifiStatus = WiFi.disconnect();
    isWifiConnected = false;
}

HttpResponse EspWifiClient::sendGetRequest(String server, uint16_t port, String urlResource, uint8_t timeoutSeconds){
    HttpResponse httpResponse;

    HttpClient* client = new HttpClient(*_esp, server.c_str(), port);
    client->setHttpResponseTimeout(timeoutSeconds * 1000);

    if(client->get(urlResource) == 0){
        httpResponse.statusCode = client->responseStatusCode();
        httpResponse.payload = client->responseBody();
    }
    delete(client);

    httpResponse.success = httpResponse.statusCode != 0 ? true : false;
    return httpResponse;
}

HttpResponse EspWifiClient::sendPostJsonRequest(String server, uint16_t port, String urlResource, String jsonPayload, uint8_t timeoutSeconds){
    HttpResponse httpResponse;

    HttpClient* client = new HttpClient(*_esp, server.c_str(), port);
    client->setHttpResponseTimeout(timeoutSeconds * 1000);

    if(client->post(urlResource, JSON_CONTENT_TYPE, jsonPayload) == 0){
        httpResponse.statusCode = client->responseStatusCode();
        httpResponse.payload = client->responseBody();
    }
    delete(client);

    httpResponse.success = httpResponse.statusCode != 0 ? true : false;
    return httpResponse;
}