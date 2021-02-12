#ifndef SoftwareHealthcheck_H
#define SoftwareHealthcheck_H

#include <stdint.h>
#include "Healthchecks/IHealthcheck.h"

class SoftwareHealthcheck : public IHealthcheck
{
public:
    SoftwareHealthcheck();
    HealthStatus check() override;

private:
    void handleCheckStatus(HealthStatus healthStatus) override;
    uint8_t _healthErrorDetectionCount = 0;
};

#endif