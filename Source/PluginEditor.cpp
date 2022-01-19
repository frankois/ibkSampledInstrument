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
    : AudioProcessorEditor (&p), mEnvelope(p), audioProcessor (p)
{
    auto ibksi = juce::ImageCache::getFromMemory(BinaryData::ibksi_png , BinaryData::ibksi_pngSize);

    jassert(ibksi.isValid());
    
    mImageComponentIbksi.setImage(ibksi, juce::RectanglePlacement::stretchToFit);
    
    addAndMakeVisible(mImageComponentIbksi);
    addAndMakeVisible(mEnvelope);
    addAndMakeVisible(mEffects);
    
    setSize (982, 460);
}

IbkSampledInstrumentAudioProcessorEditor::~IbkSampledInstrumentAudioProcessorEditor()
{
}

//==============================================================================
void IbkSampledInstrumentAudioProcessorEditor::paint (juce::Graphics& g)
{
    mImageComponentIbksi.setBounds(0,0,982,460);
    mEnvelope.setBounds(280, 50, 200, 200);
    mEffects.setBounds(520, 50, 200, 200);
}

void IbkSampledInstrumentAudioProcessorEditor::resized()
{
}
