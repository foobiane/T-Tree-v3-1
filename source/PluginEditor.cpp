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
    setSize(800, 450);
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