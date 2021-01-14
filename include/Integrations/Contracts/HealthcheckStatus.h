class HealthcheckStatus
{
public:
    long TimeStamp;
    float Internal5Voltage;
    float Internal3_3Voltage;
    float InputVoltage;
    bool IsOnReservePower;

    bool IsPMSSensorOnline;
    bool IsBMESensorOnline;
    bool IsTVOCSensorOnline;
    bool IsDHTSensorOnline;

    bool IsErrorFound;
    char* ErrorMessage;
};