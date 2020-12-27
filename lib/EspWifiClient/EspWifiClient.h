#include <stdint.h>
#include <stream.h>
#include "WiFiEspClient.h"

class EspWifiClient
{
public:
  struct HttpResponse {
      bool success;
      uint8_t statusCode;
      String payload;
  };

  EspWifiClient(uint8_t pinRx, uint8_t pinTx);
  EspWifiClient(Stream* stream);

  bool initEsp(bool waitUntilConnected = false);  

  bool connectWifi(const char* ssid, const char* password, uint8_t timeoutSeconds = 10);
  void disconnectWifi();  

  HttpResponse sendGetRequest(String server, uint16_t port, String query, uint8_t timeoutSeconds = 5);

  bool isEspReady;
  bool isWifiConnected;

private:
  WiFiEspClient* _esp;
  Stream* _espSerial;

  uint8_t _pinRx;
  uint8_t _pinTx;

  String _wifiSsid;
  String _wifiPassword;
  int _wifiStatus;
};