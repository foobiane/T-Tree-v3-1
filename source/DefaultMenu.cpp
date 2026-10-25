#include "DefaultMenu.h"

#include "PluginEditor.h"
#include "ConfigMenu.h"

DefaultMenu::DefaultMenu(PluginEditor& editor, ConfigMenu& configMenu) :
    editor(editor),
    configMenu(configMenu),
    scanButton(std::make_unique<MenuButton>("> Scan", [this](){ scanTask(); })),
    editConfigButton(std::make_unique<MenuButton>("> Edit Config", [this]() { editConfigTask(); }))
{
    addAndMakeVisible(*scanButton);
    addAndMakeVisible(*editConfigButton);
}

DefaultMenu::BackgroundTStickConfigurerThread::BackgroundTStickConfigurerThread(DefaultMenu& menu, std::shared_ptr<DefaultMenu::TStickInfo>& info) :
    juce::Thread("BackgroundTStickConfigurerThread"),
    menu(menu),
    info(info)
{
}

void DefaultMenu::BackgroundTStickConfigurerThread::run() {
    PuaraAPI::SerialManager::changeConfig(info->port, menu.configMenu.getConfig());
    info->status = TStickStatus::CONFIGURED;
    info->configButton->setText("> Configured " + info->name + "!");
    info->configButton->onClick = std::function<void()>();
}

void DefaultMenu::configureTask(const std::string& name) {
    std::shared_ptr<TStickInfo> info = tStickInfos[name];

    info->status = TStickStatus::CONFIGURING;
    info->configButton->setText("> Configuring " + info->name + "...");

    BackgroundTStickConfigurerThread(*this, info).startThread();
}

void DefaultMenu::scanTask() {
    PuaraAPI::SerialManager::scan(ports);
    std::vector<std::string> names = PuaraAPI::SerialManager::sendCommandMultiple(ports, "whatareyou");

    for (size_t i = 0; i < names.size(); i++) {
        std::string& name = names[i];

        if (!name.empty() && !tStickInfos.contains(name)) {
            tStickInfos[name] = std::make_shared<TStickInfo>(
                name,
                ports[i],
                TStickStatus::DETECTED,
                std::make_unique<MenuButton>("> Configure " + names[i], [this, name](){ configureTask(name); })
            );
        }
    }
}

void DefaultMenu::editConfigTask() {
    editor.setActiveMenu(configMenu);
}

void DefaultMenu::resized() {
    scanButton->setBounds(20, 20, getWidth() - 40, 50);
    editConfigButton->setBounds(20, 20 + 60, getWidth() - 40, 50);

    int i = 2;
    for (auto& [k, v] : tStickInfos) {
        v->configButton->setBounds(20, 20 + 60 * i, getWidth() - 40, 50);
        i++;
    }
}

void DefaultMenu::paint(juce::Graphics& g) {
    // nothing
}