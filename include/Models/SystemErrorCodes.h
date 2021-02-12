#ifndef SYSTEM_ERROR_CODES_H
#define SYSTEM_ERROR_CODES_H

enum class SystemErrorSeverity { SystemError, SystemWarning};

enum class SystemErrorCode {
    Unknown = 0, 
    HandledNoncriticalException = 1, 
    CriticalException = 2, 

    Network_WifiConnectionFailure = 30,
    Network_BackendServerConnectionFailure = 31,
    Network_BackendServerInternalError = 32
};

#endif