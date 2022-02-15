/*
  ==============================================================================

    ChorusBlock.cpp
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "ChorusBlock.h"

void ChorusBlock::prepareToPlay (juce::dsp::ProcessSpec& spec)
{
    mChorus.reset();
    mChorus.prepare (spec);
    
    isPrepared = true;
}

void ChorusBlock::process (juce::AudioBuffer<float>& buffer)
{
    jassert (isPrepared);
    
    juce::dsp::AudioBlock<float> block {buffer};
    mChorus.process (juce::dsp::ProcessContextReplacing<float> { block });
    
}

void ChorusBlock::updateParameters (const float rate, const float depth, const float centreDelay, const float feedback, const float mix)
{
    mChorus.setRate(rate);
    mChorus.setDepth(depth);
    mChorus.setCentreDelay(centreDelay);
    mChorus.setFeedback(feedback);
    mChorus.setMix(mix);
}

void ChorusBlock::reset()
{
    mChorus.reset();
}
