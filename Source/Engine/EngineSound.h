/*
  ==============================================================================

    EngineSound.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class EngineSound : public juce::SynthesiserSound
{
public:
    EngineSound (const juce::String& name,
                  juce::AudioFormatReader& source,
                  const juce::BigInteger& midiNotes,
                  int midiNoteForNormalPitch,
                  double maxSampleLengthSeconds);
    
    ~EngineSound();
    
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiNoteNumber) override;
    
    juce::AudioBuffer<float>* getAudioBuffer() const noexcept { return mAudioBuffer.get(); }
    const juce::String& getName() const noexcept { return mName; }
    int getSampleLength() const { return mSampleLength; }
    double getSampleRate() const { return mSampleRate; }
    int getMidiRootNote() const { return mMidiRootNote; }

private:
    juce::String mName;
    std::unique_ptr<juce::AudioBuffer<float>> mAudioBuffer;
    double mSampleRate;
    juce::BigInteger mMidiNotes;
    int mSampleLength = 0;
    int mMidiRootNote = 0;

    JUCE_LEAK_DETECTOR (EngineSound);
    
};
