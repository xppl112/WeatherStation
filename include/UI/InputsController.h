#ifndef INPUTSCONTROLLER_H
#define INPUTSCONTROLLER_H

#include "HardwareModules/HardwareModulesRegistry.h"
#include <Bounce2.h>

enum class ButtonPressed {NONE, TOUCH};

class InputsController
{
public:
    InputsController(HardwareModulesRegistry* hardwareModulesRegistry);
    ButtonPressed updateInputs();

private:
    Bounce2::Button* _touchButton;

    Bounce2::Button* registerButton(HardwareModulesRegistry* hardwareModulesRegistry, uint8_t buttonPin);
};

#endif