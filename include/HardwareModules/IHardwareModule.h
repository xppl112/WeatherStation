#ifndef IHardwareModule_H
#define IHardwareModule_H

class IHardwareModule
{
    public:
        virtual void connect() = 0;
        virtual bool isConnected() = 0;
};

#endif