#pragma once

#include "Menu.h"
#include "MenuButton.h"
#include "SerialManager.h"

class ConfigMenu;
class PluginEditor;

class DefaultMenu : public Menu {
public:
    DefaultMenu(PluginEditor& editor, ConfigMenu& configMenu);

    virtual void resized();
    virtual void paint(juce::Graphics& g);
    
private:
    PluginEditor& editor;
    ConfigMenu& configMenu; 

    enum TStickStatus {
        DETECTED,
        CONFIGURING,
        CONFIGURED
    };

    struct TStickInfo {
        TStickInfo(const std::string& name, PuaraAPI::SerialManager::SerialPort& port, TStickStatus status, std::shared_ptr<MenuButton> configButton) :
            name(name),
            port(port),
            status(status),
            configButton(std::move(configButton))
        {}

        std::string name;
        PuaraAPI::SerialManager::SerialPort port;
        TStickStatus status;
        std::shared_ptr<MenuButton> configButton;
    };

    std::vector<PuaraAPI::SerialManager::SerialPort> ports;
    std::unordered_map<std::string, std::shared_ptr<TStickInfo>> tStickInfos;

    std::unique_ptr<MenuButton> scanButton;
    std::unique_ptr<MenuButton> editConfigButton;

    /**
     * Task that runs when the "> Configure TStick_XXX" button is pressed
     * @param name The name of the T-Stick we are configuring
     */
    void configureTask(const std::string& name);

    /**
     * Task that runs when the "> Scan" button is pressed
     */
    void scanTask();

    /**
     * Task that runs when the "> Edit Config" button is pressed
     */
    void editConfigTask();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DefaultMenu)
};