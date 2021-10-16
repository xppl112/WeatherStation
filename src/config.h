#include <Arduino.h>
#include <MCPExtender.h>

#ifndef CONFIG_H
#define CONFIG_H

const uint8_t VOLTMETER_ANALOG_PIN = A0;
const int VOLTMETER_R1 = 19400;
const int VOLTMETER_R2 = 6740;
const float VOLTMETER_ALERT_THRESHOLD_DANGEROUS = 5.6;
const float VOLTMETER_ALERT_THRESHOLD_TOP = 5.3;
const float VOLTMETER_ALERT_THRESHOLD_BOTTOM = 4.6;

const uint8_t OLED_I2C_ADDR = 0x3C;
const uint8_t BME_I2C_ADDR = 0x76;
const uint8_t MCP_EXTENDER_I2C_ADDR = 0x20;

const uint8_t TM1637_CLK_PIN = D7;
const uint8_t TM1637_DATA_PIN = D6;

const uint8_t RGB_LED_R_PIN = D4;
const uint8_t RGB_LED_G_PIN = D3;
const uint8_t RGB_LED_B_PIN = D0;

//Hardware UART pins used
//const uint8_t PLANTOWER_RX_PIN = D9;
//const uint8_t PLANTOWER_TX_PIN = D10;

const uint8_t DHT_DATA_PIN = D5;

const uint8_t LED_POWER = MCP_A3;
const uint8_t LED_POWER_NIGHT = MCP_A2;

const uint8_t LED_STATUS = MCP_B1;
const uint8_t LED_DATA_TRANSFER = MCP_A0;
const uint8_t LED_ERROR_STATUS = MCP_B0;

const uint8_t LED_UNIVERSAL_RGB_R = MCP_B3;
const uint8_t LED_UNIVERSAL_RGB_G = MCP_B4;
const uint8_t LED_UNIVERSAL_RGB_B = MCP_B5;

const uint8_t LED_PRESSURE_RED = MCP_B2;
const uint8_t LED_PRESSURE_GREEN = MCP_A1;

const uint8_t UP_BUTTON_PIN = MCP_A7;
const uint8_t RIGHT_BUTTON_PIN = MCP_A6;
const uint8_t DOWN_BUTTON_PIN = MCP_A5;
const uint8_t LEFT_BUTTON_PIN = MCP_A4;

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
const uint8_t SOFTWARE_ERRORS_RESTART_LIMIT = 10;

const uint8_t WEATHER_MONITOR_INTERVAL_SECONDS = 60;
const uint8_t WEATHER_MONITOR_MEASUREMENT_DURATION_SECONDS = 10; //60 - standard

const uint8_t HEALTHCHECK_MONITOR_INTERVAL_SECONDS = 20;
const uint8_t SYSTEM_STATUS_REPORT_INTERVAL_SECONDS = 60;
const uint8_t TIME_UPDATE_INTERVAL_SECONDS = 180;

const uint8_t MENU_REFRESH_INTERVAL_SECONDS = 2;
const uint8_t USER_INTERACTION_TIMEOUT_SECONDS = 30;

// night-mode
const uint8_t WEATHER_MONITOR_INTERVAL_NIGHT_SECONDS = 30;
const uint8_t NIGHT_MODE_HOUR_FROM = 0;
const uint8_t NIGHT_MODE_HOUR_TO = 8;

const uint8_t TIMEZONE_HOURS_OFFSET = 2;//TODO: move to server

#endif