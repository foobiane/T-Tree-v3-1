/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ConfigMenu.h"
#include "DefaultMenu.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p) : 
    AudioProcessorEditor(&p), 
    audioProcessor(p),
    defaultMenu(*this, configMenu),
    configMenu(*this, defaultMenu),
    activeMenu(&defaultMenu)
{
    auto monitorArea = getParentMonitorArea();
    setSize(monitorArea.getWidth(), monitorArea.getHeight() - 50);

    // setOpaque(false);
    // addToDesktop(0);
    // juce::Desktop::getInstance().setKioskModeComponent(this, false);

    addAndMakeVisible(activeMenu);
}

PluginEditor::~PluginEditor()
{
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void PluginEditor::resized()
{
    activeMenu->setBounds(getLocalBounds());
}

void PluginEditor::setActiveMenu(Menu& menu) {
    removeChildComponent(activeMenu);
    activeMenu = &menu;
    addAndMakeVisible(activeMenu);
    
    resized();
}