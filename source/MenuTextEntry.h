#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class MenuTextEntry : public juce::Component {
public:
    MenuTextEntry(const std::string& labelText, std::function<void(juce::TextEditor&)> onTextChange, const std::string& backgroundText, const std::string& initialText = "");

    virtual void resized();
    virtual void paint(juce::Graphics& g);

private:
    juce::Label label;
    juce::TextEditor textEntry;
};