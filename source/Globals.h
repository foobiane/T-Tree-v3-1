#pragma once

#include <juce_graphics/juce_graphics.h>
#include <BinaryData.h>

const juce::Font APP_FONT = juce::Font(
    juce::Typeface::createSystemTypefaceFor(
        BinaryData::JetBrainsMonoRegular_ttf, 
        BinaryData::JetBrainsMonoRegular_ttfSize
    )
).withHeight(24.0f);