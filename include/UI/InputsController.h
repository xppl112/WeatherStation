#include <BounceMcp.h>
#include "MCPExtender.h"

enum ButtonPressed {NONE, LEFT, CENTER, RIGHT, LEFTRIGHT};

class InputsController
{
public:
    InputsController();
    ButtonPressed updateInputs();

private:
    MCPExtender* _mcp;
    Button* _leftButton;
    Button* _centerButton;
    Button* _rightButton;
};