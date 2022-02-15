/*
  ==============================================================================

    EnvelopeGui.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "CommonGui.h"

//==============================================================================
/*
*/
class EnvelopeGui  : public juce::Component
{
public:
    EnvelopeGui (juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId);
    ~EnvelopeGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    
    juce::Label mAttackLabel{"AttackLabel","Attack"}, mDecayLabel{"DecayLabel","Decay"}, mSustainLabel{"SustainLabel","Sustain"}, mReleaseLabel{"ReleaseLabel","Release"};
    
    std::vector<juce::Slider*> mEnvelopeSliders = { &mAttackSlider, &mDecaySlider, &mSustainSlider, &mReleaseSlider };
    std::vector<juce::Label*> mEnvelopeLabels = { &mAttackLabel, &mDecayLabel, &mSustainLabel, &mReleaseLabel };
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mReleaseAttachment;
    
    juce::String mComponentName {""};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeGui)
};
