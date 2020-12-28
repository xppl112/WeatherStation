#include <Arduino.h>
#include "MCPExtender.h"

MCPExtender::MCPExtender(uint8_t i2c_address)
{
    _mcp = new Adafruit_MCP23017();
    _i2c_address = i2c_address;
}

void MCPExtender::connect(){
    _mcp->begin(_i2c_address);
    /*Wire.begin();
    Wire.beginTransmission(0x20);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();*/
}

/*!
 * @brief Sets specified pin mode
 * @param pin Pin to read
 * @param direction INPUT or OUTPUT
 * @param pullup LOW, HIGH or -1
 */
void MCPExtender::pinMode(uint8_t pin, uint8_t direction, int8_t pullup)
{
    _mcp->pinMode(pin, direction);
    if(pullup != -1)_mcp->pullUp(pin, pullup);
}

uint8_t MCPExtender::digitalRead(uint8_t pin)
{
    return _mcp->digitalRead(pin);
}

void MCPExtender::digitalWrite(uint8_t pin, uint8_t value)
{
    _mcp->digitalWrite(pin, value);
   /* Wire.beginTransmission(0x20);
    Wire.write(0x12);
    Wire.write(0xfe);
    Wire.write(0xfd);
    Wire.write(0xfb);
    Wire.write(0xf7);
    Wire.write(0xef);
    Wire.write(0xdf);
    Wire.write(0xbf);
    Wire.write(0x7f);
    Wire.endTransmission();*/
}