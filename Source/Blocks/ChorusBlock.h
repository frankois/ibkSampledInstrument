/*
  ==============================================================================

    ChorusBlock.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ChorusBlock
{
public:
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void process (juce::AudioBuffer<float>& buffer);
    void updateParameters (const float rate, const float depth, const float centreDelay, const float feedback, const float mix);
    void reset();
    
private:
    juce::dsp::Chorus<float> mChorus;
    bool isPrepared { false };
};
