#include "EspWifiClient.h"



EspWifiClient* esp;


esp = new EspWifiClient(&Serial);
  esp->initEsp();



  esp->connectWifi(ssid.c_str(), password.c_str());
  EspWifiClient::HttpResponse response = esp->sendGetRequest(server, port, query);
  if(response.success){
    dConsole+=response.statusCode;
    dConsole+=" - ";
    dConsole+=response.payload;
  }
  else {
    dConsole+="WIFI FAILURE";
  } 
  esp->disconnectWifi();
