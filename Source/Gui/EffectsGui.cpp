/*
  ==============================================================================

    EffectsGui.cpp

    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EffectsGui.h"

//==============================================================================
EffectsGui::EffectsGui (juce::AudioProcessorValueTreeState& apvts, juce::String rateId, juce::String depthId, juce::String centreDelayId, juce::String feedbackId, juce::String mixId, juce::String lfoRateId, juce::String lfoDepthId)
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
    mFxFiveLabel.attachToComponent(&mFxFiveSlider, false);
    mFxSixLabel.attachToComponent(&mFxSixSlider, false);
    mFxSevenLabel.attachToComponent(&mFxSevenSlider, false);
    mFxEightLabel.attachToComponent(&mFxEightSlider, false);
    mFxNineLabel.attachToComponent(&mFxNineSlider, false);
    mFxTenLabel.attachToComponent(&mFxTenSlider, false);
    
    // APVTS config
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    mRateAttachment = std::make_unique<SliderAttachment> (apvts, rateId, mFxOneSlider);
    mDepthAttachment = std::make_unique<SliderAttachment> (apvts, depthId, mFxTwoSlider);
    mCentreDelayAttachment = std::make_unique<SliderAttachment> (apvts, centreDelayId, mFxThreeSlider);
    mFeedbackAttachment = std::make_unique<SliderAttachment> (apvts, feedbackId, mFxFourSlider);
    mMixAttachment = std::make_unique<SliderAttachment> (apvts, mixId, mFxFiveSlider);
    
    mLfoRate = std::make_unique<SliderAttachment> (apvts, lfoRateId, mFxSixSlider);
    mLfoDepth = std::make_unique<SliderAttachment> (apvts, lfoDepthId, mFxSevenSlider);
}

EffectsGui::~EffectsGui()
{
    mEffectsLabels.clear();
    mEffectsLabels.shrink_to_fit();
    mEffectsSliders.clear();
    mEffectsSliders.shrink_to_fit();
}

void EffectsGui::paint (juce::Graphics& g)
{
    
//    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    const auto otherOffsetY = 105.0f;
    
    const auto chorusBackgroundBorder = juce::Rectangle<float>(0.0f, 2.0f, 19.0f, 94.0f);
    const auto chorusBackground = juce::Rectangle<float>(2.0f, 4.0f, 15.0f, 90.0f);
    
    const auto otherBackgroundBorder = juce::Rectangle<float>(0.0f, otherOffsetY + 0.0f, 19.0f, 94.0f);
    const auto otherBackground = juce::Rectangle<float>(2.0f, otherOffsetY + 2.0f, 15.0f, 90.0f);
    
    g.setColour(juce::Colours::black);
    g.fillRect(chorusBackgroundBorder);
    g.fillRect(otherBackgroundBorder);
    
    g.setColour(gIbkColour);
    g.fillRect(chorusBackground);
    g.fillRect(otherBackground);
    
    juce::Font titleFont = juce::Font(juce::Font::getDefaultSansSerifFontName(), 13.0f, juce::Font::bold);
    g.setFont(titleFont);
    g.setColour (juce::Colours::white);
    g.drawMultiLineText ("CHORUS", 9 , 20.0f, 1.0f, juce::Justification::centred);
    g.drawMultiLineText ("LFO-P", 9 , 130.0f, 1.0f, juce::Justification::centred);
}

void EffectsGui::resized()
{
    const auto sliderWidth = 80;
    const auto sliderHeight = 80;
    
    const auto labelWidth = sliderWidth;
    const auto labelHeight = 15;
    
    const auto coordOriginX = 15;
    const auto coordOriginSliderY = 15;
    const auto coordOriginLabelY = 5;
    const auto coordOffsetSliderY = coordOriginSliderY + sliderHeight + labelHeight + 10;
    const auto coordOffsetLabelY = coordOriginLabelY + sliderHeight + labelHeight + 10;
    
    
    mFxOneSlider.setBounds(coordOriginX, coordOriginSliderY, sliderWidth, sliderHeight);
    mFxOneLabel.setBounds(coordOriginX, coordOriginLabelY, labelWidth, labelHeight);
    
    mFxTwoSlider.setBounds(coordOriginX + sliderWidth, coordOriginSliderY, sliderWidth, sliderHeight);
    mFxTwoLabel.setBounds(coordOriginX + sliderWidth, coordOriginLabelY, labelWidth, labelHeight);
    
    mFxThreeSlider.setBounds(coordOriginX + 2 * sliderWidth, coordOriginSliderY, sliderWidth, sliderHeight);
    mFxThreeLabel.setBounds(coordOriginX + 2 * sliderWidth, coordOriginLabelY, labelWidth, labelHeight);
    
    mFxFourSlider.setBounds(coordOriginX + 3 * sliderWidth, coordOriginSliderY, sliderWidth, sliderHeight);
    mFxFourLabel.setBounds(coordOriginX + 3 * sliderWidth, coordOriginLabelY, labelWidth, labelHeight);
    
    mFxFiveSlider.setBounds(coordOriginX + 4 * sliderWidth, coordOriginSliderY, sliderWidth, sliderHeight);
    mFxFiveLabel.setBounds(coordOriginX + 4 * sliderWidth, coordOriginLabelY, labelWidth, labelHeight);
    
    mFxSixSlider.setBounds(coordOriginX, coordOffsetSliderY, sliderWidth, sliderHeight);
    mFxSixLabel.setBounds(coordOriginX, coordOffsetLabelY, labelWidth, labelHeight);

    mFxSevenSlider.setBounds(coordOriginX + sliderWidth, coordOffsetSliderY, sliderWidth, sliderHeight);
    mFxSevenLabel.setBounds(coordOriginX + sliderWidth, coordOffsetLabelY, labelWidth, labelHeight);

    mFxEightSlider.setBounds(coordOriginX + 2 * sliderWidth, coordOffsetSliderY, sliderWidth, sliderHeight);
    mFxEightLabel.setBounds(coordOriginX + 2 * sliderWidth, coordOffsetLabelY, labelWidth, labelHeight);

    mFxNineSlider.setBounds(coordOriginX + 3 * sliderWidth, coordOffsetSliderY, sliderWidth, sliderHeight);
    mFxNineLabel.setBounds(coordOriginX + 3 * sliderWidth, coordOffsetLabelY, labelWidth, labelHeight);

    mFxTenSlider.setBounds(coordOriginX + 4 * sliderWidth, coordOffsetSliderY, sliderWidth, sliderHeight);
    mFxTenLabel.setBounds(coordOriginX + 4 * sliderWidth, coordOffsetLabelY, labelWidth, labelHeight);
}
