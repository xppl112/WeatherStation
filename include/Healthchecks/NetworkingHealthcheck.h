#ifndef NetworkingHealthcheck_H
#define NetworkingHealthcheck_H

#include <map>
#include "HardwareModules/HardwareModulesRegistry.h"
#include "Healthchecks/IHealthcheck.h"

enum class NetworkingStatus {
    UNKNOWN, 
    OK, 
    WIFI_CONNECTION_FAILED, 
    BACKEND_SERVER_CONNECTION_FAILED, 
    BACKEND_SERVER_ERROR};

class NetworkingHealthcheck : public IHealthcheck
{
public:
    NetworkingHealthcheck();
    HealthStatus check() override;
    NetworkingStatus getStatus(){ return _status; };

private:
    void handleCheckStatus(HealthStatus healthStatus) override;
    NetworkingStatus _status;
};

#endif