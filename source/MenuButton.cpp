#include "MenuButton.h"

MenuButton::MenuButton(const std::string& text, const std::function<void()>& onClick) :
    juce::Button("MenuButton-" + std::to_string(id)),
    text(text)
{
    this->onClick = onClick;
    id++;
}

void MenuButton::setText(const std::string& text) {
    this->text = text;
    resized();
}

void MenuButton::paintButton(juce::Graphics& g, bool isHighlighted, bool isDown) {
    if (isHighlighted || isDown) {
        g.fillAll(juce::Colours::white);
        g.setColour(juce::Colours::black);
    }
    else {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);

        // Draw a white top and bottom border if the button is black
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
    
    g.setFont(APP_FONT);
    g.drawFittedText(text, juce::Rectangle<int>(10, 10, getWidth() - 20, getHeight() - 20), juce::Justification::centredLeft, 1);
}