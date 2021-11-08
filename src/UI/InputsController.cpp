#include "UI/InputsController.h"
#include "Config.h"

InputsController::InputsController(HardwareModulesRegistry* hardwareModulesRegistry){
    _touchButton = registerButton(hardwareModulesRegistry, TOUCH_BUTTON_PIN);
}

ButtonPressed InputsController::updateInputs(){
    _touchButton->update();

    bool touchButtonPressed = _touchButton->pressed();
    if (touchButtonPressed) return ButtonPressed::TOUCH;

    return ButtonPressed::NONE;
}

Bounce2::Button* InputsController::registerButton(HardwareModulesRegistry* hardwareModulesRegistry, uint8_t buttonPin){
    Bounce2::Button* button = new Bounce2::Button(); 
    button->attach(buttonPin , INPUT);
    button->interval(5);
    button->setPressedState(HIGH);

    return button;
}