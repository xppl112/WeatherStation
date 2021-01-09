#include "RGBLed.h"

#include "MCPExtender.h"

RGBLed* rgb;
MCPExtender* mcp;

  rgb = new RGBLed(3, 5, 6, false);
  rgb->setColor(0, 0, 0);

    mcp = new MCPExtender(0x20);
  mcp->connect();
  mcp->pinMode(MCP_A0, OUTPUT);
  mcp->pinMode(MCP_B0, OUTPUT);
  mcp->pinMode(MCP_A1, INPUT);
  mcp->pinMode(MCP_B1, INPUT);


  dConsole = "a1: ";
int a1 = mcp->digitalRead(MCP_A1);
int b1 = mcp->digitalRead(MCP_B1);
dConsole += a1;
dConsole += "; b1: ";
dConsole += b1;
mcp->digitalWrite(MCP_A0, HIGH);
mcp->digitalWrite(MCP_B0, HIGH);
