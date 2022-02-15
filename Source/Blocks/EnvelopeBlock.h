/*
  ==============================================================================

    EnvelopeBlock.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EnvelopeBlock : public juce::ADSR
{
public:
    void updateEnvelope (const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters mEnvelopeParameters;
};
