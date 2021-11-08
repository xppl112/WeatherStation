#include <Arduino.h>

#ifndef CONFIG_H
#define CONFIG_H

const uint8_t LIGHT_SENSOR_PIN = A0;

const uint8_t TM1637_CLK_PIN = D7;
const uint8_t TM1637_DATA_PIN = D6;

const uint8_t RGB_LED_R_PIN = D4;
const uint8_t RGB_LED_G_PIN = D3;
const uint8_t RGB_LED_B_PIN = D0;

//Hardware I2C pins used
//const uint8_t I2C_SCL = D1;
//const uint8_t I2C_SDA = D2;
const uint8_t BME_I2C_ADDR = 0x76;

//Hardware UART pins used
//const uint8_t PLANTOWER_RX_PIN = D9;
//const uint8_t PLANTOWER_TX_PIN = D10;

const uint8_t DHT_DATA_PIN = D5;
const uint8_t TOUCH_BUTTON_PIN = D8;

struct BackendClientConfig {
    const char* WifiSSID = "xppl";
    const char* WifiPassword = "william2015";

    const char* ServerHost = "http://weather.liashko.space";
    const char* ServerApiGetTimeUrl = "/api/time";
    const char* ServerApiPostWeatherDataUrl = "/api/weather";

    int BatchRequestsMaxSize = 5;
};

const uint8_t DATA_COLLECTION_CAPACITY = 100;

const uint8_t LIGHT_SCAN_INTERVAL_SECONDS = 60;
const uint8_t WEATHER_MONITOR_INTERVAL_SECONDS = 60;
const uint8_t WEATHER_MONITOR_MEASUREMENT_DURATION_SECONDS = 60;

const uint8_t TIME_UPDATE_INTERVAL_SECONDS = 100;

// night-mode
const uint8_t WEATHER_MONITOR_INTERVAL_NIGHT_SECONDS = 300;

#endif