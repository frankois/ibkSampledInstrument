/*
  ==============================================================================

    EngineVoice.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EngineSound.h"
#include "../Blocks/EnvelopeBlock.h"
#include "../Blocks/ChorusBlock.h"

class EngineVoice : public juce::SynthesiserVoice
{
public:
    EngineVoice();
    ~EngineVoice();
    
    bool canPlaySound (juce::SynthesiserSound*) override;

    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound*, int pitchWheel) override;
    void stopNote (float velocity, bool allowTailOff) override;

    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;

    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer<float>&, int startSample, int numSamples) override;
    void voiceCustomProcess (juce::AudioBuffer<float>& audioBuffer, int numSamples);
    
    void updateAmpEnvelope (const float attack, const float decay, const float sustain, const float release);
    void updateChorus (const float rate, const float depth, const float centreDelay, const float feedback, const float mix);
    
    
private:
    double mPitchRatio = 0;
    double mSamplePosition = 0.0;
    float mVelocity = 0.0f;
    
    juce::AudioBuffer<float> mSynthBuffer;
    EnvelopeBlock mAmpEnvelope;
    ChorusBlock mChorus;
    
    bool isPrepared { false };

    JUCE_LEAK_DETECTOR (EngineVoice)
};
