/*
  ==============================================================================

    EngineSampler.cpp
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "EngineSampler.h"
#include "../Utils/UtilsFiles.h"

void EngineSampler::setup()
{
    clearSounds();

    for (int i = 0; i < mNumVoices; i++)
        addVoice(new EngineVoice());
    
    std::unique_ptr<juce::AudioFormatReader> audioReader (mWavFormat.createReaderFor (createSamplesInputStream ("os_synth.wav").release(), true));
    mAllNotes.setRange (0, 128, true);
    addSound (new EngineSound ("vox", *audioReader, mAllNotes, 74, 30.0));
}

void EngineSampler::prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
{
    setCurrentPlaybackSampleRate (sampleRate);
    for (int i = 0; i < getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<EngineVoice*>(getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, numChannels);
        }
    }
}

