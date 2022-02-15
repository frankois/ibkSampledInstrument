/*
  ==============================================================================

    EngineSampler.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EngineVoice.h"
#include "EngineSound.h"

class EngineSampler : public juce::Synthesiser
{
public:
    void setup();
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels);
    
private:
    juce::WavAudioFormat mWavFormat;
    juce::BigInteger mAllNotes;
    
    static const int mNumVoices = 16;
};
