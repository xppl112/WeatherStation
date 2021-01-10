#include <Arduino.h>
#include "UI/LEDIndicatorsController.h"

LEDIndicatorsController::LEDIndicatorsController(){
    _pollutionRGBLed = new RGBLed(3, 5, 6, false);
    _mcp = new MCPExtender(0x20);
    _mcp->connect();
    _mcp->pinMode(MCP_A0, OUTPUT);
    _mcp->pinMode(MCP_B0, OUTPUT);
    _mcp->pinMode(MCP_A1, INPUT);
    _mcp->pinMode(MCP_B1, INPUT);
}

void LEDIndicatorsController::setPollutionLevel(){
    _pollutionRGBLed->setColor(0, 0, 0);
}

void LEDIndicatorsController::setStatusLed(){    
    //int a1 = _mcp->digitalRead(MCP_A1);
    //int b1 = _mcp->digitalRead(MCP_B1);
    _mcp->digitalWrite(MCP_A0, HIGH);
    _mcp->digitalWrite(MCP_B0, HIGH);
}