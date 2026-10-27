#include "ConfigMenu.h"

#include "DefaultMenu.h"
#include "PluginEditor.h"

using std::placeholders::_1;

ConfigMenu::ConfigMenu(PluginEditor& editor, DefaultMenu& defaultMenu) :
    editor(editor),
    defaultMenu(defaultMenu),
    backButton(std::make_unique<MenuButton>("> Back", [this](){ backButtonTask(); }))
{
    auto updateJson = [this](juce::Label& l, const std::string& jsonKey, bool isNumber = false){
        if (isNumber) {
            config[jsonKey] = std::stoi(l.getText().toStdString());
        }
        else {
            config[jsonKey] = l.getText().toStdString();
        }
    };

    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>("SSID", std::bind(updateJson, _1, "wifiSSID"))));
    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>("Password", std::bind(updateJson, _1, "wifiPSK"))));
    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>("Destination IP", std::bind(updateJson, _1, "oscIP1"))));
    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>("Destination Port", std::bind(updateJson, _1, "oscPORT1", true))));

    for (auto& configTextEntry : configTextEntries) {
        addAndMakeVisible(*configTextEntry);
    }

    addAndMakeVisible(*backButton);
}

void ConfigMenu::backButtonTask() {
    editor.setActiveMenu(defaultMenu);
}

void ConfigMenu::resized() {
    int i = 0;
    for (auto& configTextEntry : configTextEntries) {
        configTextEntry->setBounds(20, 20 + 60 * i, getWidth() - 40, 50);
        i++;
    }
    backButton->setBounds(20, getHeight() - 70, getWidth() - 40, 50);
}

void ConfigMenu::paint(juce::Graphics& g) {
    // nothing
}