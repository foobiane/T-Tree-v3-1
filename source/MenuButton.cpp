#include "MenuButton.h"

MenuButton::MenuButton(const std::string& text, const std::function<void()>& onClick) :
    juce::Button("MenuButton-" + std::to_string(id)),
    text(text)
{
    this->onClick = [this, onClick](){
        if (this->activated) {
            onClick();
        }
    };
    id++;
}

void MenuButton::setText(const std::string& text) {
    this->text = text;
    repaint();
}

void MenuButton::setSubText(const std::string& text) {
    this->subText = text;
    repaint();
}

void MenuButton::toggleActivated() {
    activated = !activated;
    repaint();
}

void MenuButton::paintButton(juce::Graphics& g, bool isHighlighted, bool isDown) {
    juce::Colour textColour;

    if (activated && (isHighlighted || isDown)) {
        g.fillAll(juce::Colours::white);
        // g.setColour(juce::Colours::black);
        textColour = juce::Colours::black;
    }
    else {
        g.fillAll(juce::Colours::black);
        textColour = (activated ? juce::Colours::white : juce::Colours::grey);

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

    g.setColour(textColour);
    g.setFont(APP_FONT);
    g.drawFittedText(text, juce::Rectangle<int>(10, 10, getWidth() - 20, getHeight() - 20), juce::Justification::centredLeft, 1);

    if (!subText.empty()) {
        g.setColour(juce::Colours::white);
        g.setFont(APP_FONT);
        g.drawFittedText(subText, juce::Rectangle<int>(10, 10, getWidth() - 20, getHeight() - 20), juce::Justification::centredRight, 1);
    }
}