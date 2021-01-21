#ifndef INPUTSCONTROLLER_H
#define INPUTSCONTROLLER_H

#include "HardwareModules/HardwareModulesRegistry.h"
#include <BounceMcp.h>

enum class ButtonPressed {NONE, LEFT, UP, RIGHT, DOWN, LEFTRIGHT};

class InputsController
{
public:
    InputsController(HardwareModulesRegistry* hardwareModulesRegistry);
    ButtonPressed updateInputs();

private:
    Button* _leftButton;
    Button* _rightButton;    
    Button* _upButton;
    Button* _downButton;

    Button* registerButton(HardwareModulesRegistry* hardwareModulesRegistry, uint8_t buttonPin);
};

#endif