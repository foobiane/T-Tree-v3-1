#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

#include "BinaryData.h"
#include "ConfigMenu.h"
#include "DefaultMenu.h"
#include "Globals.h"
#include "Menu.h"
// #include "MenuButton.h"

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    PluginEditor(PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void setActiveMenu(Menu& menu);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginProcessor& audioProcessor;

    Menu* activeMenu;
    DefaultMenu defaultMenu;
    ConfigMenu configMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
