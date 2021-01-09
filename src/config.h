#include <Arduino.h>

const uint8_t OLED_I2C_ADDR = 0x3C;
const uint8_t LCD_I2C_ADDR = 0x27;
const uint8_t BME_I2C_ADDR = 0x76;
const uint8_t MCP_EXTENDER_I2C_ADDR = 0x20;

const uint8_t RGB_LED_R_PIN = 3;
const uint8_t RGB_LED_G_PIN = 5;
const uint8_t RGB_LED_B_PIN = 6;

const uint8_t PLANTOWER_RX_PIN = 8;
const uint8_t PLANTOWER_TX_PIN = 9;

const char*  WIFI_SSID = "xppl";
const char*  WIFI_PASSWORD = "william2015";

const char* SERVER_HOST = "194.58.70.17";
const uint16_t SERVER_PORT = 5100;
const char* SERVER_API_GET_TIME = "/api/time";
const char* SERVER_API_POST_WEATHER = "/api/weather";
