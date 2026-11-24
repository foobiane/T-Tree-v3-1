#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "Globals.h"

static unsigned long long id = 0; 

class MenuButton : public juce::Button {
public:
    MenuButton(const std::string& text, const std::function<void()>& onClick);

    void setText(const std::string& text, juce::Colour customColour = juce::Colours::white);
    void setSubText(const std::string& text);
    void toggleActivated();

    virtual void paintButton(juce::Graphics&, bool, bool);
    
private:
    juce::Colour customColour = juce::Colours::white;
    std::string text;
    std::string subText;
    bool activated = true;
};