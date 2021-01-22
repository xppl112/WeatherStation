#include <map>
#include "HardwareModules/HardwareModulesRegistry.h"
#include "Healthchecks/HealthcheckProvider.h"
#include "InputsController.h"
#include "MenuConfiguration.h"
#include "OLED.h"

class MenuController
{
public:
    MenuController(HardwareModulesRegistry* hardwareModulesRegistry, HealthcheckProvider* healthCheckProvider);
    void showMenu(MenuMode menuMode = MAIN_MENU_MODE);
    void buttonPressed(ButtonPressed button);

    bool isMenuActive() { return _menuMode != OFF_MENU_MODE; }

private:
    HealthcheckProvider* _healthCheckProvider;

    OLED* _screen;
    volatile MenuMode _menuMode = OFF_MENU_MODE;
    volatile int _menuOptionSelectedIndex = 0;
    MenuConfiguration _menuConfiguration;
    MenuScreen getCurrentScreen() { return _menuConfiguration.getMenuScreen(_menuMode); }
    MenuOption getSelectedOption() { return _menuConfiguration.getMenuScreen(_menuMode).options[_menuOptionSelectedIndex]; }
    int getCurrentScreenOptionsCount() { return _menuConfiguration.getMenuScreen(_menuMode).options.size(); }

    void updateMenu();
    void printMenu();

    void showDevicesInfo();
    void showDebugScreen();

    void selectNextOption();
    void selectPreviousOption();
    void clickOption();
    void returnBack();
};