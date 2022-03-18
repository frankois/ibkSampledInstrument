/*
  ==============================================================================

    EffectsGui.h
    
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
class EffectsGui  : public juce::Component
{
public:
    EffectsGui (juce::AudioProcessorValueTreeState& apvts, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId, juce::String lfoRateId, juce::String lfoDepthId);
    ~EffectsGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mFxOneSlider, mFxTwoSlider, mFxThreeSlider, mFxFourSlider, mFxFiveSlider, mFxSixSlider, mFxSevenSlider, mFxEightSlider, mFxNineSlider, mFxTenSlider;
    
    juce::Label mFxOneLabel{"FxOneLabel", "Rate"}, mFxTwoLabel{"FxTwoLabel", "Depth"}, mFxThreeLabel{"FxThreeLabel", "Centre Delay"}, mFxFourLabel{"FxFourLabel", "Feedback"}, mFxFiveLabel{"FxFiveLabel", "Mix"}, mFxSixLabel{"FxSixLabel", "Rate"}, mFxSevenLabel{"FxSevenLabel", "Depth"}, mFxEightLabel{"FxEightLabel", "FX #8"}, mFxNineLabel{"FxNineLabel", "FX #9"}, mFxTenLabel{"FxTenLabel", "FX #10"};
    
    std::vector<juce::Slider*> mEffectsSliders = { &mFxOneSlider, &mFxTwoSlider, &mFxThreeSlider, &mFxFourSlider, &mFxFiveSlider, &mFxSixSlider, &mFxSevenSlider, &mFxEightSlider, &mFxNineSlider, &mFxTenSlider };
    std::vector<juce::Label*> mEffectsLabels = { &mFxOneLabel, &mFxTwoLabel, &mFxThreeLabel, &mFxFourLabel, &mFxFiveLabel, &mFxSixLabel, &mFxSevenLabel, &mFxEightLabel, &mFxNineLabel, &mFxTenLabel };
    
    // Chorus
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mRateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mCentreDelayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFeedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mMixAttachment;
    
    // LFO
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mLfoRate;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mLfoDepth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsGui)
};
