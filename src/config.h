#include <Arduino.h>
#include <MCPExtender.h>

#ifndef CONFIG_H
#define CONFIG_H

const uint8_t OLED_I2C_ADDR = 0x3C;
const uint8_t BME_I2C_ADDR = 0x76;
const uint8_t MCP_EXTENDER_I2C_ADDR = 0x20;

const uint8_t RGB_LED_R_PIN = D4;
const uint8_t RGB_LED_G_PIN = D3;
const uint8_t RGB_LED_B_PIN = D0;

//Hardware UART pins used
//const uint8_t PLANTOWER_RX_PIN = D9;
//const uint8_t PLANTOWER_TX_PIN = D10;

const uint8_t DHT_DATA_PIN = D5;

const uint8_t LED_POWER = MCP_A0;
const uint8_t LED_POWER_NIGHT = MCP_B0;
const uint8_t LED_STATUS = MCP_A1;
const uint8_t LED_TEMPERATURE = MCP_A2;
const uint8_t LED_PRESSURE = MCP_A3;

const uint8_t UP_BUTTON_PIN = MCP_A4;
const uint8_t LEFT_BUTTON_PIN = MCP_A5;
const uint8_t DOWN_BUTTON_PIN = MCP_A6;
const uint8_t RIGHT_BUTTON_PIN = MCP_A7;

struct BackendClientConfig {
    const char* WifiSSID = "xppl";
    const char* WifiPassword = "william2015";

    const char* ServerHost = "http://194.58.70.17:5100";
    const char* ServerApiGetTimeUrl = "/api/time";
    const char* ServerApiPostWeatherDataUrl = "/api/weather";
    const char* ServerApiPostHealthStatusUrl = "/api/status";

    int BatchRequestsMaxSize = 5;
};

const uint8_t DATA_COLLECTION_CAPACITY = 100;

const uint8_t WEATHER_MONITOR_INTERVAL_SECONDS = 5;
const uint8_t WEATHER_MONITOR_MEASUREMENT_DURATION_SECONDS = 10; //60 - standard

const uint8_t HEALTHCHECK_MONITOR_INTERVAL_SECONDS = 60;
const uint8_t SYSTEM_STATUS_REPORT_INTERVAL_SECONDS = 60;
const uint8_t TIME_UPDATE_INTERVAL_SECONDS = 60;

// night-mode
const uint8_t WEATHER_MONITOR_INTERVAL_NIGHT_SECONDS = 30;

#endif