#ifndef MENU_CONFIGURATION_H
#define MENU_CONFIGURATION_H

#include <map>

#define MAIN_MENU_MODE MenuMode::MAIN_MENU
#define OFF_MENU_MODE MenuMode::MENU_OFF
#define DEBUG_MENU_MODE MenuMode::MENU_DEBUG_MODE

enum class MenuMode {MENU_OFF, MAIN_MENU, MENU_SETTINGS, MENU_DEVICES_INFO, MENU_DEBUG_MODE};

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
            {MenuMode::MAIN_MENU, MenuScreen {
                .title = "Main menu",
                .previousScreen = MenuMode::MENU_OFF,
                .options = {
                    MenuOption {
                        .title = "Settings",
                        .nextScreen = MenuMode::MENU_SETTINGS
                    }, 
                    MenuOption {
                        .title = "Devices info",
                        .nextScreen = MenuMode::MENU_DEVICES_INFO
                    }, 
                }
            }},
            {MenuMode::MENU_SETTINGS, MenuScreen {
                .title = "Settings",
                .previousScreen = MenuMode::MAIN_MENU,
                .options = {
                    MenuOption {
                        .title = "Option 1",
                        .nextScreen = MenuMode::MENU_SETTINGS
                    }, 
                    MenuOption {
                        .title = "Option 2",
                        .nextScreen = MenuMode::MENU_SETTINGS
                    }, 
                }
            }},
            {MenuMode::MENU_DEVICES_INFO, MenuScreen {
                .title = "Devices info",
                .previousScreen = MenuMode::MAIN_MENU
            }}
        };
        return menuBindings;
    }
};

#endif