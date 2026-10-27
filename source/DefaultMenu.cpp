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

void DefaultMenu::configureTask(const std::string& name) {
    std::shared_ptr<TStickInfo> info = tStickInfos[name];

    info->status = TStickStatus::CONFIGURING;
    info->configButton->toggleActivated();
    info->configButton->setText("> Configuring " + info->name + "...");

    std::shared_ptr<PuaraAPI::SerialManager::ChangeConfigProgress> progress = std::make_shared<PuaraAPI::SerialManager::ChangeConfigProgress>();

    // Config progress watch thread
    juce::Thread::launch([this, info, progress](){
        std::unique_lock lk(progress->mtx);

        {
            juce::MessageManagerLock mmLock;
            info->configButton->setSubText("0%");
        }

        do {
            progress->cv.wait(lk);
            int progressPercentage = 100.0f * ((double) progress->numFieldsChanged / (double) progress->numFieldsTotal);

            {
                juce::MessageManagerLock mmLock;
                info->configButton->setSubText(std::to_string(progressPercentage) + "%");
            }
        }
        while (progress->numFieldsChanged < progress->numFieldsTotal);
    });

    // Main configuration thread
    juce::Thread::launch([this, info, progress](){
        PuaraAPI::SerialManager::changeConfig(info->port, configMenu.getConfig(), progress.get());
        
        info->status = TStickStatus::CONFIGURED;

        {
            juce::MessageManagerLock mmLock;
            info->configButton->setText("> Configured " + info->name + "!");
            info->configButton->setSubText("");
            resized();
        }
    });
}

void DefaultMenu::scanTask() {
    scanButton->setText("> Scanning...");

    juce::Thread::launch([this](){
        std::vector<PuaraAPI::SerialManager::SerialPort> ports; 
        PuaraAPI::SerialManager::scan(ports);

        std::vector<std::string> names = PuaraAPI::SerialManager::sendCommandMultiple(ports, "whatareyou");

        for (size_t i = 0; i < names.size(); i++) {
            std::string& name = names[i];

            if (name != "ERROR" && !tStickInfos.contains(name)) {
                auto configButton = std::make_shared<MenuButton>("> Configure " + names[i], [this, name](){configureTask(name);});
                
                tStickInfos[name] = std::make_shared<TStickInfo>(
                    name,
                    ports[i],
                    TStickStatus::DETECTED,
                    configButton
                );

                {
                    juce::MessageManagerLock mmLock;
                    addAndMakeVisible(*configButton);
                }
            }
        }

        {
            juce::MessageManagerLock mmLock;
            scanButton->setText("> Scan");
            resized();
        }
    });
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