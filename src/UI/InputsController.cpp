#include "UI/InputsController.h"
#include "GlobalObjects/GlobalDevices.h"
#include "Config.h"
extern GlobalDevices* globalDevices;

InputsController::InputsController(){
    _leftButton = new Button(globalDevices->mcpExtender); 
    _leftButton->attach( LEFT_BUTTON_PIN , INPUT_PULLUP );
    _leftButton->interval(5);
    _leftButton->setPressedState(LOW);

    _centerButton = new Button(globalDevices->mcpExtender); 
    _centerButton->attach( CENTER_BUTTON_PIN , INPUT_PULLUP );
    _centerButton->interval(5);
    _centerButton->setPressedState(LOW);

    _rightButton = new Button(globalDevices->mcpExtender); 
    _rightButton->attach( RIGHT_BUTTON_PIN , INPUT_PULLUP );
    _rightButton->interval(5);
    _rightButton->setPressedState(LOW);
}

ButtonPressed InputsController::updateInputs(){
    _leftButton->update();
    _centerButton->update();
    _rightButton->update();

    bool leftButtonPressed = _leftButton->pressed();
    bool centerButtonPressed = _centerButton->pressed();
    bool rightButtonPressed = _rightButton->pressed();    

    if (leftButtonPressed && rightButtonPressed) return ButtonPressed::LEFTRIGHT;
    else if (leftButtonPressed) return ButtonPressed::LEFT;
    else if (centerButtonPressed) return ButtonPressed::CENTER;
    else if (rightButtonPressed) return ButtonPressed::RIGHT;

    return ButtonPressed::NONE;
}