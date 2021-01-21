#include "UI/MenuController.h"

MenuController::MenuController(HardwareModulesRegistry* hardwareModulesRegistry){
    _screen = hardwareModulesRegistry->oledScreen;
}

void MenuController::showMenu(MenuMode menuMode){
    _menuMode = menuMode;
    _menuOptionSelectedIndex = 0;
    updateMenu();
}

void MenuController::updateMenu(){
    switch(_menuMode){
        case MenuMode::MAIN_MENU:
        case MenuMode::MENU_SETTINGS:
            printMenu();
            break;
        case MenuMode::MENU_DEVICES_INFO:
            showDevicesInfo();
            break;
        case MenuMode::MENU_DEBUG_MODE:
            break;
    }
}

void MenuController::buttonPressed(ButtonPressed button){
    switch(button){
        case ButtonPressed::LEFT:
            returnBack();
            break;
        case ButtonPressed::RIGHT:
            clickOption();            
            break;
        case ButtonPressed::UP:
            selectPreviousOption();
            break;
        case ButtonPressed::DOWN:
            selectNextOption();
            break;
        case ButtonPressed::LEFTRIGHT:break;
        case ButtonPressed::NONE:break;
    }
}

void MenuController::showDevicesInfo(){
    printMenu();
}

void MenuController::showDebugScreen(){
    printMenu();
}

void MenuController::printMenu(){
    MenuScreen menuScreen = getCurrentScreen();
    int selectedOption = _menuOptionSelectedIndex;

    _screen->setWordWrapMode(false);
    _screen->clear();

    _screen->setCursor(0,12);
    _screen->print(menuScreen.title, FONT_TITLE);

    for(int i=0; i<menuScreen.options.size();i++){
        if(selectedOption == i){
            _screen->setCursor(2, 30 + i*16);_screen->print("||" + menuScreen.options.at(i).title, FONT_SMALL);   
        }         
        else {
            _screen->setCursor(10, 30 + i*16);_screen->print(menuScreen.options.at(i).title, FONT_SMALL_THIN);
        }
    }

    _screen->render();
}

void MenuController::selectNextOption(){
    _menuOptionSelectedIndex++;
    if(_menuOptionSelectedIndex >= getCurrentScreenOptionsCount()) _menuOptionSelectedIndex = getCurrentScreenOptionsCount()-1;
    updateMenu();
}

void MenuController::selectPreviousOption(){
    _menuOptionSelectedIndex--;
    if(_menuOptionSelectedIndex < 0) _menuOptionSelectedIndex = 0;
    updateMenu();
}

void MenuController::clickOption(){
    showMenu(getSelectedOption().nextScreen);
}

void MenuController::returnBack(){
    showMenu(getCurrentScreen().previousScreen);
}