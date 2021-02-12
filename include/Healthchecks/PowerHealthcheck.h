#ifndef PowerHealthcheck_H
#define PowerHealthcheck_H

#include "Healthchecks/IHealthcheck.h"

class PowerHealthcheck : public IHealthcheck
{
public:
    PowerHealthcheck();
    HealthStatus check() override;
    float getInputVoltage();

private:
    void handleCheckStatus(HealthStatus healthStatus) override;
};

#endif