/*
  ==============================================================================

    EngineVoice.cpp
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "EngineVoice.h"

EngineVoice::EngineVoice() {}
EngineVoice::~EngineVoice() {}

bool EngineVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<const EngineSound*> (sound) != nullptr;
}

void EngineVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* s, int /*currentPitchWheelPosition*/)
{
    if (auto* sound = dynamic_cast<const EngineSound*> (s))
    {
        mPitchRatio = std::pow (2.0, (midiNoteNumber - sound->getMidiRootNote()) / 12.0)
                        * sound->getSampleRate() / getSampleRate();

        mSamplePosition = 0.0;
        mVelocity = velocity;
        
        mAmpEnvelope.noteOn();
    }
    else
    {
        jassert(false);
    }
}

void EngineVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        mAmpEnvelope.noteOff();
    }
    else
    {
        clearCurrentNote();
        mAmpEnvelope.reset();
    }
}

void EngineVoice::pitchWheelMoved (int newPitchWheelValue) {}
void EngineVoice::controllerMoved (int controllerNumber, int newControllerValue) {}

void EngineVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
    
    mAmpEnvelope.setSampleRate (sampleRate);
    mChorus.prepareToPlay (spec);
    
    isPrepared = true;
}

//==============================================================================
void EngineVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert (isPrepared);
    
    if (auto* playingSound = static_cast<EngineSound*> (getCurrentlyPlayingSound().get()))
    {
        mSynthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
        mSynthBuffer.clear();
        juce::dsp::AudioBlock<float> audioBlock { mSynthBuffer };
        
        auto& data = *playingSound->getAudioBuffer();
        const float* const inL = data.getReadPointer (0);
        const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer (1) : nullptr;

        float* outL = outputBuffer.getWritePointer (0, startSample);
        float* outR = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer (1, startSample) : nullptr;
        
        auto procBufPointers = mSynthBuffer.getArrayOfWritePointers();

        for (int i = 0; i < numSamples; ++i)
        {
            auto pos = (int) mSamplePosition;
            auto alpha = (float) (mSamplePosition - pos);
            auto invAlpha = 1.0f - alpha;

            float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
            float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
                                       : l;

            auto envelopeValue = mAmpEnvelope.getNextSample();

            l *= mVelocity * envelopeValue;
            r *= mVelocity * envelopeValue;
            
            procBufPointers[0][i] = l * mVelocity;
            procBufPointers[1][i] = r * mVelocity;
            
            mSamplePosition += mPitchRatio;

            if (mSamplePosition > playingSound->getSampleLength())
            {
                stopNote (0.0f, false);
                break;
            }
        }
        
        voiceCustomProcess (mSynthBuffer, numSamples);
        
        for (int i = 0; i < numSamples; ++i)
        {
            jassert (outR != nullptr);

            outL[i] += procBufPointers[0][i];
            outR[i] += procBufPointers[1][i];
        }
    }
}

void EngineVoice::voiceCustomProcess (juce::AudioBuffer<float>& audioBuffer, int numSamples)
{
    mAmpEnvelope.applyEnvelopeToBuffer (audioBuffer, 0, numSamples);
    mChorus.process (audioBuffer);
}


void EngineVoice::updateAmpEnvelope(const float attack, const float decay, const float sustain, const float release)
{
    mAmpEnvelope.updateEnvelope (attack, decay, sustain, release);
}

void EngineVoice::updateChorus (const float rate, const float depth, const float centreDelay, const float feedback, const float mix)
{
    mChorus.updateParameters (rate, depth, centreDelay, feedback, mix);
}
