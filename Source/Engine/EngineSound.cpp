/*
  ==============================================================================

    EngineSound.cpp
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "EngineSound.h"

EngineSound::EngineSound (const juce::String& soundName,
                            juce::AudioFormatReader& source,
                            const juce::BigInteger& notes,
                            int midiNoteForNormalPitch,
                            double maxSampleLengthSeconds)
    : mName (soundName)
    , mSampleRate (source.sampleRate)
    , mMidiNotes (notes)
    , mMidiRootNote (midiNoteForNormalPitch)
{
    if (mSampleRate > 0 && source.lengthInSamples > 0)
    {
        mSampleLength = juce::jmin ((int) source.lengthInSamples, (int) (maxSampleLengthSeconds * mSampleRate));
        mAudioBuffer.reset (new juce::AudioBuffer<float> (juce::jmin (2, (int) source.numChannels), mSampleLength + 4));
        source.read (mAudioBuffer.get(), 0, mSampleLength + 4, 0, true, true);
    }
}

EngineSound::~EngineSound() {}

bool EngineSound::appliesToNote (int midiNoteNumber)
{
    return mMidiNotes[midiNoteNumber];
}

bool EngineSound::appliesToChannel (int midiChannel)
{
    return true;
}
