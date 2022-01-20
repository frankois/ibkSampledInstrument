/*
  ==============================================================================

    EnvelopeComponent.cpp
 
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeComponent.h"

//==============================================================================
EnvelopeComponent::EnvelopeComponent(IbkSampledInstrumentAudioProcessor& p) : audioProcessor(p)
{
    const auto sliderType = juce::Slider::SliderStyle::LinearVertical;
    
    // Sliders config
    for (auto i = 0; i < mEnvelopeSliders.size(); i++)
    {
        mEnvelopeSliders[i]->setSliderStyle(sliderType);
        mEnvelopeSliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, true, gSliderTextWidth, gSliderTextHeight);
        mEnvelopeSliders[i]->setColour(juce::Slider::ColourIds::thumbColourId, gIbkColour);
        mEnvelopeSliders[i]->setColour(juce::Slider::ColourIds::textBoxTextColourId, gTextColour);
        mEnvelopeSliders[i]->setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, gIbkColour);
        addAndMakeVisible(mEnvelopeSliders[i]);
    }
    
    // Labels config
    for (auto i = 0; i < mEnvelopeLabels.size(); i++)
    {
        mEnvelopeLabels[i]->setFont(gLabelFontSize);
        mEnvelopeLabels[i]->setColour(juce::Label::ColourIds::textColourId, gIbkColour);
        mEnvelopeLabels[i]->setJustificationType(juce::Justification::centred);
    }
    
    // Sliders/Labels config
    mAttackLabel.attachToComponent(&mAttackSlider, false);
    mDecayLabel.attachToComponent(&mDecaySlider, false);
    mSustainLabel.attachToComponent(&mSustainSlider, false);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);
    
    // APVTS config
    mAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "ATTACK", mAttackSlider);
    
    mDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "DECAY", mDecaySlider);
    
    mSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "SUSTAIN", mSustainSlider);
    
    mReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.getAPVTS(), "RELEASE", mReleaseSlider);
}

EnvelopeComponent::~EnvelopeComponent()
{
    mEnvelopeLabels.clear();
    mEnvelopeLabels.shrink_to_fit();
    mEnvelopeSliders.clear();
    mEnvelopeSliders.shrink_to_fit();
}

void EnvelopeComponent::paint (juce::Graphics& g)
{
}

void EnvelopeComponent::resized()
{
    const auto coordOriginX = 0;
    const auto coordOriginY = 0;
    
    const auto sliderWidth = 50;
    const auto sliderHeight = 170;
    const auto sliderSpacingX = sliderWidth;
    const auto sliderOffset = 25;
    
    mAttackSlider.setBounds(coordOriginX, coordOriginY + sliderOffset, sliderWidth, sliderHeight);
    mDecaySlider.setBounds(coordOriginX + sliderSpacingX, coordOriginY + sliderOffset, sliderWidth, sliderHeight);
    mSustainSlider.setBounds(coordOriginX + 2*sliderSpacingX, coordOriginY + sliderOffset, sliderWidth, sliderHeight);
    mReleaseSlider.setBounds(coordOriginX + 3*sliderSpacingX, coordOriginY + sliderOffset, sliderWidth, sliderHeight);

}
