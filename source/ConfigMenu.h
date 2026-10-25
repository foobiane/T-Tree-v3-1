#pragma once

#include "Menu.h"
#include "MenuButton.h"
#include "MenuTextEntry.h"

#include <SerialManager.h>

class DefaultMenu;
class PluginEditor;

class ConfigMenu : public Menu {
public:
    ConfigMenu(PluginEditor& editor, DefaultMenu& defaultMenu);

    virtual void resized();
    virtual void paint(juce::Graphics& g);

    json getConfig() { return config; }
private:
    PluginEditor& editor;
    DefaultMenu& defaultMenu;

    std::vector<std::unique_ptr<MenuTextEntry>> configTextEntries;
    std::unique_ptr<MenuButton> backButton;

    void backButtonTask();

    json config;
};