/*
  ==============================================================================

    EffectsComponent.h
    
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Utils/UtilsUI.h"

//==============================================================================
/*
*/
class EffectsComponent  : public juce::Component
{
public:
    EffectsComponent();
    ~EffectsComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mFxOneSlider, mFxTwoSlider, mFxThreeSlider, mFxFourSlider;
    
    juce::Label mFxOneLabel{"FxOneLabel", "FX #1"}, mFxTwoLabel{"FxTwoLabel", "FX #2"}, mFxThreeLabel{"FxThreeLabel", "FX #3"}, mFxFourLabel{"FxFourLabel", "FX #4"};
    
    std::vector<juce::Slider*> mEffectsSliders = { &mFxOneSlider, &mFxTwoSlider, &mFxThreeSlider, &mFxFourSlider };
    std::vector<juce::Label*> mEffectsLabels = { &mFxOneLabel, &mFxTwoLabel, &mFxThreeLabel, &mFxFourLabel };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsComponent)
};
