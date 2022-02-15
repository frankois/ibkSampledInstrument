/*
  ==============================================================================

    PluginEditor.h
 
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Gui/EnvelopeGui.h"
#include "Gui/EffectsGui.h"

//==============================================================================
/**
*/
class IbkSampledInstrumentAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    IbkSampledInstrumentAudioProcessorEditor (IbkSampledInstrumentAudioProcessor&);
    ~IbkSampledInstrumentAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    IbkSampledInstrumentAudioProcessor& audioProcessor;
    juce::ImageComponent mImageComponentIbksi;
    EnvelopeGui mEnvelopeGui;
    EffectsGui mEffectsGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IbkSampledInstrumentAudioProcessorEditor)
};
