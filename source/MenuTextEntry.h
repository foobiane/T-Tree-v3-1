#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class MenuTextEntry : public juce::Component {
public:
    MenuTextEntry(const std::string& labelText, std::function<void(juce::TextEditor&)> onTextChange, const std::string& backgroundText, const std::string& initialText = "");

#ifdef RASPBERRY_PI_USE_VIRTUAL_KEYBOARD
    class VirtualKeyboardTextEntry : public juce::TextEditor {
    public:
        void focusGained(FocusChangeType) override {
            proc.start("wvkbd-mobintl");
        }
        void focusLost(FocusChangeType) override {
            proc.kill();
        }
    private:
        juce::ChildProcess proc;
    };
#endif

    virtual void resized();
    virtual void paint(juce::Graphics& g);

private:
    juce::Label label;

#ifdef RASPBERRY_PI_USE_VIRTUAL_KEYBOARD
    VirtualKeyboardTextEntry textEntry;
#else
    juce::TextEditor textEntry;
#endif

};