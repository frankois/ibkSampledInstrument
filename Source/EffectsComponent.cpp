/*
  ==============================================================================

    EffectsComponent.cpp

    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EffectsComponent.h"

//==============================================================================
EffectsComponent::EffectsComponent()
{
    const auto sliderType = juce::Slider::SliderStyle::RotaryVerticalDrag;
    
    // Sliders configuration
    for (auto i = 0; i < mEffectsSliders.size(); i++)
    {
        mEffectsSliders[i]->setSliderStyle(sliderType);
        mEffectsSliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, true, gSliderTextWidth, gSliderTextHeight);
        mEffectsSliders[i]->setColour(juce::Slider::ColourIds::thumbColourId, gIbkColour);
        mEffectsSliders[i]->setColour(juce::Slider::ColourIds::textBoxTextColourId, gTextColour);
        mEffectsSliders[i]->setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, gIbkColour);
        mEffectsSliders[i]->setRange(1, 1000, 1);
        addAndMakeVisible(mEffectsSliders[i]);
    }

    // Labels configuration
    for (auto i = 0; i < mEffectsLabels.size(); i++)
    {
        mEffectsLabels[i]->setFont(gLabelFontSize);
        mEffectsLabels[i]->setColour(juce::Label::ColourIds::textColourId, gIbkColour);
        mEffectsLabels[i]->setColour(juce::Slider::ColourIds::textBoxTextColourId, gTextColour);
        mEffectsLabels[i]->setJustificationType(juce::Justification::centred);
    }

    mFxOneLabel.attachToComponent(&mFxOneSlider, false);
    mFxTwoLabel.attachToComponent(&mFxTwoSlider, false);
    mFxThreeLabel.attachToComponent(&mFxThreeSlider, false);
    mFxFourLabel.attachToComponent(&mFxFourSlider, false);
}

EffectsComponent::~EffectsComponent()
{
    mEffectsLabels.clear();
    mEffectsLabels.shrink_to_fit();
    mEffectsSliders.clear();
    mEffectsSliders.shrink_to_fit();
}

void EffectsComponent::paint (juce::Graphics& g)
{
}

void EffectsComponent::resized()
{
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    
    const auto labelWidth = sliderWidth;
    const auto labelHeight = 15;
    
    mFxOneSlider.setBounds(0, 15, sliderWidth, sliderHeight);
    mFxOneLabel.setBounds(0, 5, labelWidth, labelHeight);
    
    mFxTwoSlider.setBounds(105, 15, sliderWidth, sliderHeight);
    mFxTwoLabel.setBounds(105, 5, labelWidth, labelHeight);
    
    mFxThreeSlider.setBounds(0, 115, sliderWidth, sliderHeight);
    mFxThreeLabel.setBounds(0, 105, labelWidth, labelHeight);
    
    mFxFourSlider.setBounds(105, 115, sliderWidth, sliderHeight);
    mFxFourLabel.setBounds(105, 105, labelWidth, labelHeight);
}
