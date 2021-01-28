#ifndef SoftwareHealthcheck_H
#define SoftwareHealthcheck_H

#include <map>
#include "Healthchecks/IHealthcheck.h"

class SoftwareHealthcheck : public IHealthcheck
{
public:
    SoftwareHealthcheck();
    HealthStatus check() override;

private:
    void handleCheckStatus(HealthStatus healthStatus) override;
};

#endif