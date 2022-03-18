/*
  ==============================================================================

    PluginEditor.cpp
 
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IbkSampledInstrumentAudioProcessorEditor::IbkSampledInstrumentAudioProcessorEditor (IbkSampledInstrumentAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , mEnvelopeGui ("Amp Envelope", audioProcessor.getAPVTS(), "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , mEffectsGui (audioProcessor.getAPVTS(), "RATE", "DEPTH", "CENTREDELAY", "FEEDBACK", "MIX", "LFORATE", "LFODEPTH")
    
{
    auto ibksi = juce::ImageCache::getFromMemory(BinaryData::ibksi_png , BinaryData::ibksi_pngSize);

    jassert(ibksi.isValid());
    
    mImageComponentIbksi.setImage(ibksi, juce::RectanglePlacement::stretchToFit);
    
    addAndMakeVisible(mImageComponentIbksi);
    addAndMakeVisible(mEnvelopeGui);
    addAndMakeVisible(mEffectsGui);
    setSize (982, 460);
}

IbkSampledInstrumentAudioProcessorEditor::~IbkSampledInstrumentAudioProcessorEditor()
{
}

//==============================================================================
void IbkSampledInstrumentAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void IbkSampledInstrumentAudioProcessorEditor::resized()
{
    mImageComponentIbksi.setBounds(0,0,982,460);
    mEnvelopeGui.setBounds(280, 50, 200, 200);
    mEffectsGui.setBounds(520, 50, 415, 200);
}
