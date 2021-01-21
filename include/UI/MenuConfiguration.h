#ifndef MENU_CONFIGURATION_H
#define MENU_CONFIGURATION_H

#include <map>

#define MAIN_MENU_MODE MenuMode::MAIN_MENU
#define OFF_MENU_MODE MenuMode::MENU_OFF
#define DEBUG_MENU_MODE MenuMode::MENU_DEBUG_MODE

enum MenuMode {MENU_OFF, MAIN_MENU, MENU_SETTINGS, MENU_DEVICES_INFO, MENU_DEBUG_MODE};

struct MenuOption {
    String title;
    MenuMode nextScreen;
};

struct MenuScreen {
    String title;
    MenuMode previousScreen;
    std::vector<MenuOption> options;
};

struct MenuConfiguration {
public:
    MenuScreen getMenuScreen(MenuMode menuMode){
        return getMenuBindings()[menuMode];
    }

private:
    std::map<MenuMode, MenuScreen>& getMenuBindings()
    {
        static std::map<MenuMode, MenuScreen> menuBindings = {
            {MAIN_MENU, MenuScreen {
                .title = "Main menu",
                .previousScreen = MENU_OFF,
                .options = {
                    MenuOption {
                        .title = "Settings",
                        .nextScreen = MENU_SETTINGS
                    }, 
                    MenuOption {
                        .title = "Devices info",
                        .nextScreen = MENU_DEVICES_INFO
                    }, 
                }
            }},
            {MENU_SETTINGS, MenuScreen {
                .title = "Settings",
                .previousScreen = MAIN_MENU,
                .options = {
                    MenuOption {
                        .title = "Option 1",
                        .nextScreen = MENU_SETTINGS
                    }, 
                    MenuOption {
                        .title = "Option 2",
                        .nextScreen = MENU_SETTINGS
                    }, 
                }
            }},
            {MENU_DEVICES_INFO, MenuScreen {
                .title = "Devices info",
                .previousScreen = MAIN_MENU
            }}
        };
        return menuBindings;
    }
};

#endif