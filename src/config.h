#include <Arduino.h>

#ifndef CONFIG_H
#define CONFIG_H

const uint8_t OLED_I2C_ADDR = 0x3C;
//const uint8_t LCD_I2C_ADDR = 0x27;
const uint8_t BME_I2C_ADDR = 0x76;
const uint8_t MCP_EXTENDER_I2C_ADDR = 0x20;

const uint8_t RGB_LED_R_PIN = 3;
const uint8_t RGB_LED_G_PIN = 5;
const uint8_t RGB_LED_B_PIN = 6;

const uint8_t PLANTOWER_RX_PIN = 8;
const uint8_t PLANTOWER_TX_PIN = 9;

struct BackendClientConfig {
    const char* WifiSSID = "xppl";
    const char* WifiPassword = "william2015";

    const char* ServerHost = "194.58.70.17";
    const static uint16_t ServerPort = 5100;
    const char* ServerApiGetTimeUrl = "/api/time";
    const char* ServerApiPostWeatherDataUrl = "/api/weather";

};
const uint8_t WEATHER_MONITOR_INTERVAL_SECONDS = 60;
const uint8_t WEATHER_MONITOR_MEASUREMENT_DURATION_SECONDS = 30;

#endif