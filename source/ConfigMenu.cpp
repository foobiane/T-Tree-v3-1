#include "ConfigMenu.h"

#include "DefaultMenu.h"
#include "PluginEditor.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using std::placeholders::_1;

ConfigMenu::ConfigMenu(PluginEditor& editor, DefaultMenu& defaultMenu) :
    editor(editor),
    defaultMenu(defaultMenu),
    backButton(std::make_unique<MenuButton>("> Back", [this](){ backButtonTask(); }))
{
    if (fs::exists(fs::path("./default.json"))) {
        std::ifstream defaultConfigStream("./default.json");
        config = json::parse(defaultConfigStream);
    }

    auto updateJson = [this](juce::TextEditor& e, const std::string& jsonKey, bool isNumber = false){
        if (isNumber) {
            config[jsonKey] = std::stoi(e.getText().toStdString());
        }
        else {
            config[jsonKey] = e.getText().toStdString();
        }
    };

    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>(
        "SSID", std::bind(updateJson, _1, "wifiSSID"), "ssid", (config.contains("wifiSSID") ? config["wifiSSID"] : "")
    )));
    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>(
        "Password", std::bind(updateJson, _1, "wifiPSK"), "password", (config.contains("wifiPSK") ? config["wifiPSK"] : "")
    )));
    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>(
        "Destination IP", std::bind(updateJson, _1, "oscIP1"), "192.168.1.2", (config.contains("oscIP1") ? config["oscIP1"] : "")
    )));
    configTextEntries.push_back(std::move(std::make_unique<MenuTextEntry>(
        "Destination Port", std::bind(updateJson, _1, "oscPORT1", true), "8000", (config.contains("oscPORT1") ? std::to_string(config["oscPORT1"].get<unsigned>()) : "")
    )));

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