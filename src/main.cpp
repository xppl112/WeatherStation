#include <Arduino.h>
#include "LCD.h"
#include "OLED.h"
#include "BME280Sensor.h"
#include "EspWifiClient.h"
#include "RGBLed.h"
#include "PlantowerSensor.h"

String server = "194.58.70.17";
uint16_t port = 5100;
String query = "/api/time";
String ssid = "xppl";
String password = "william2015";

LCD* lcd;
OLED* oled;
BME280Sensor* bme;
EspWifiClient* esp;
RGBLed* rgb;
PlantowerSensor* plantower;

String dConsole;

int freeMemory();
void scanI2C();

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  rgb = new RGBLed(3, 5, 6, false);
  rgb->setColor(0, 0, 0);

  oled = new OLED(0x3C);
  oled->connect();
  oled->clear(true);
 
  lcd = new LCD(0x27, 16, 2);
  lcd->connect();
  lcd->backlight(true);

  bme = new BME280Sensor(0x76);
  bme->connect();

  plantower = new PlantowerSensor(8, 9, 7);
  plantower->connect();

  esp = new EspWifiClient(&Serial);
  esp->initEsp();
}

char* floatToString(float number, int widthBeforeDot, int widthAfterDot = 2){
  char* str = new char[widthBeforeDot + 1 + widthAfterDot];
  dtostrf(number, widthAfterDot, widthAfterDot, str);
  return str;
}


void loop() {
  digitalWrite(13, !digitalRead(13));

  char* str = new char[16];
  
  BME280Sensor::BME280Data data = bme->readData();
  
  lcd->setCursor();  
  char* measureString = floatToString(data.temperatureCelsium, 2);
  sprintf(str, "T:%s", measureString);
  lcd->print(str);
  delete measureString;
  delete str;
  
  str = new char[16];
  measureString = floatToString(data.humidityPercent, 2);
  lcd->setCursor(8, 0);
  sprintf(str, " H:%s", measureString);
  lcd->print(str);
  delete measureString;
  delete str;

  PlantowerSensor::PmsData pmsData = plantower->readDataSyncronioslyAndSleep();
  dConsole="1.0=";
  dConsole+=pmsData.PM_1_0;
  dConsole+="; ";
    dConsole+="2.5=";
  dConsole+=pmsData.PM_2_5;
  dConsole+="; ";
    dConsole+="10.0=";
  dConsole+=pmsData.PM_10_0;
  dConsole+="; ";

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

  str = new char[16];
  sprintf(str, "RAM: %d   ", freeMemory());
  lcd->setCursor(0, 1);
  lcd->print(str);
  delete str;

  oled->setWordWrapMode(true);
  oled->clear(true);
  oled->setCursor(0,0);

  if (dConsole.length() > 0) { 
        oled->print(dConsole, true);
  } 

  //delay(5000);
}



void scanI2C(){
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
 
    delay(5000);
}



#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

