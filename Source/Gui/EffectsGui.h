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
    EffectsGui (juce::AudioProcessorValueTreeState& apvts, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId);
    ~EffectsGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mFxOneSlider, mFxTwoSlider, mFxThreeSlider, mFxFourSlider, mFxFiveSlider, mFxSixSlider, mFxSevenSlider, mFxEightSlider, mFxNineSlider, mFxTenSlider;
    
    juce::Label mFxOneLabel{"FxOneLabel", "Rate"}, mFxTwoLabel{"FxTwoLabel", "Depth"}, mFxThreeLabel{"FxThreeLabel", "Centre Delay"}, mFxFourLabel{"FxFourLabel", "Feedback"}, mFxFiveLabel{"FxFiveLabel", "Mix"}, mFxSixLabel{"FxSixLabel", "FX #6"}, mFxSevenLabel{"FxSevenLabel", "FX #7"}, mFxEightLabel{"FxEightLabel", "FX #8"}, mFxNineLabel{"FxNineLabel", "FX #9"}, mFxTenLabel{"FxTenLabel", "FX #10"};
    
    std::vector<juce::Slider*> mEffectsSliders = { &mFxOneSlider, &mFxTwoSlider, &mFxThreeSlider, &mFxFourSlider, &mFxFiveSlider, &mFxSixSlider, &mFxSevenSlider, &mFxEightSlider, &mFxNineSlider, &mFxTenSlider };
    std::vector<juce::Label*> mEffectsLabels = { &mFxOneLabel, &mFxTwoLabel, &mFxThreeLabel, &mFxFourLabel, &mFxFiveLabel, &mFxSixLabel, &mFxSevenLabel, &mFxEightLabel, &mFxNineLabel, &mFxTenLabel };
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mRateAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDepthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mCentreDelayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFeedbackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mMixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsGui)
};
