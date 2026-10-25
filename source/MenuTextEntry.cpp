#include "Globals.h"
#include "MenuTextEntry.h"

MenuTextEntry::MenuTextEntry(const std::string& labelText, std::function<void(juce::Label&)> onTextChange) {
    textEntry.onTextChange = [onTextChange, this](){ onTextChange(this->textEntry); };

    label.setFont(APP_FONT);
    textEntry.setFont(APP_FONT);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    textEntry.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    textEntry.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::grey);

    label.setText(labelText, juce::NotificationType::dontSendNotification);
    textEntry.setEditable(true);

    addAndMakeVisible(label);
    addAndMakeVisible(textEntry);
}

void MenuTextEntry::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    juce::Path topBorder;
    topBorder.startNewSubPath(0, 0);
    topBorder.lineTo(getWidth(), 0);

    juce::Path bottomBorder;
    bottomBorder.startNewSubPath(0, getHeight());
    bottomBorder.lineTo(getWidth(), getHeight());

    const float BORDER_THICKNESS = 5.0f;

    g.strokePath(topBorder, juce::PathStrokeType(BORDER_THICKNESS));
    g.strokePath(bottomBorder, juce::PathStrokeType(BORDER_THICKNESS));
}

void MenuTextEntry::resized() {
    juce::Rectangle<int> bounds { 10, 10, getWidth() - 20, getHeight() - 20 };

    label.setBounds(
        bounds.getX(), 
        bounds.getY(), 
        bounds.getWidth() / 2., 
        bounds.getHeight()
    );

    textEntry.setBounds(
        bounds.getX() + bounds.getWidth() / 2., 
        bounds.getY(), 
        bounds.getWidth() / 2., 
        bounds.getHeight()
    );
}