#ifndef IHealthcheck_H
#define IHealthcheck_H

enum class HealthStatus {HEALTH_OK, HEALTH_WARNING, HEALTH_ERROR};

class IHealthcheck
{
    public:
        virtual HealthStatus check() = 0;

    private:
        virtual void handleCheckStatus(HealthStatus healthStatus);
};

#endif