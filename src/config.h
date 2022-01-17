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
    const char* ServerApiPostWeatherDataUrl = "/api/weather/PostOutdoorReportsBatch";

    const uint8_t BatchMinSize = 1;
    const uint8_t BatchMaxSize = 10;

    const uint8_t RequestsSeriesMaxSize = 5;
};

const int DATA_COLLECTION_CAPACITY = 100;

const int SENSORS_SCAN_INTERVAL_SECONDS = 30;
const uint8_t PM_SENSOR_MEASUREMENT_DURATION_CYCLES = 2;
const uint8_t PM_SENSOR_CALMDOWN_DURATION_CYCLES = 4;

const bool SENSORS_INERTION_STABILIZATION = true;
const uint8_t PM_SENSOR_INERTION_STABILIZATION_COUNT = 3;//overrides SENSORS_INERTION_STABILIZATION, set 1 to turn off

// night-mode
const uint8_t SKIP_MEASUREMENT_CYCLES_IN_NIGHT_MODE = 4;//0 = dont skip any cycle
const uint8_t SKIP_SENDING_DATA_CYCLES_IN_NIGHT_MODE = 5;//0 = dont skip any cycle

#endif