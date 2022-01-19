/*
  ==============================================================================

    EnvelopeComponent.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Utils/UtilsUI.h"

//==============================================================================
/*
*/
class EnvelopeComponent  : public juce::Component
{
public:
    EnvelopeComponent(IbkSampledInstrumentAudioProcessor& p);
    ~EnvelopeComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    
    juce::Label mAttackLabel{"AttackLabel","Attack"}, mDecayLabel{"DecayLabel","Decay"}, mSustainLabel{"SustainLabel","Sustain"}, mReleaseLabel{"ReleaseLabel","Release"};
    
    std::vector<juce::Slider*> mEnvelopeSliders = { &mAttackSlider, &mDecaySlider, &mSustainSlider, &mReleaseSlider };
    std::vector<juce::Label*> mEnvelopeLabels = { &mAttackLabel, &mDecayLabel, &mSustainLabel, &mReleaseLabel };
    
    IbkSampledInstrumentAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeComponent)
};
