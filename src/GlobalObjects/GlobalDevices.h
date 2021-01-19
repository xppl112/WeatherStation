#ifndef GLOBALDEVICES_H
#define GLOBALDEVICES_H

#include <Arduino.h>
#include "MCPExtender.h"
#include "Config.h"

class GlobalDevices {    
public:
    GlobalDevices(){        
        setupMcpExtender();
    }
    
    void setupMcpExtender(){
        mcpExtender = new MCPExtender(MCP_EXTENDER_I2C_ADDR);
        mcpExtender->connect();
    }

    MCPExtender* mcpExtender;
};
#endif