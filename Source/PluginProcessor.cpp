/*
  ==============================================================================

    PluginProcessor.cpp
 
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IbkSampledInstrumentAudioProcessor::IbkSampledInstrumentAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
    , mAPVTS (*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    mEngineSampler.setup();
}

IbkSampledInstrumentAudioProcessor::~IbkSampledInstrumentAudioProcessor()
{
}

//==============================================================================
const juce::String IbkSampledInstrumentAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IbkSampledInstrumentAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IbkSampledInstrumentAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IbkSampledInstrumentAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IbkSampledInstrumentAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IbkSampledInstrumentAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IbkSampledInstrumentAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IbkSampledInstrumentAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String IbkSampledInstrumentAudioProcessor::getProgramName (int index)
{
    return {};
}

void IbkSampledInstrumentAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void IbkSampledInstrumentAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mEngineSampler.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void IbkSampledInstrumentAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IbkSampledInstrumentAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void IbkSampledInstrumentAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i = 0; i < mEngineSampler.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<EngineVoice*>(mEngineSampler.getVoice(i)))
        {
            // Amp Envelope
            auto attack  = mAPVTS.getRawParameterValue("ATTACK")->load();
            auto decay   = mAPVTS.getRawParameterValue("DECAY")->load();
            auto sustain = mAPVTS.getRawParameterValue("SUSTAIN")->load();
            auto release = mAPVTS.getRawParameterValue("RELEASE")->load();

            // Chorus
            auto rate = mAPVTS.getRawParameterValue("RATE")->load();
            auto depth = mAPVTS.getRawParameterValue("DEPTH")->load();
            auto centreDelay = mAPVTS.getRawParameterValue("CENTREDELAY")->load();
            auto feedback = mAPVTS.getRawParameterValue("FEEDBACK")->load();
            auto mix = mAPVTS.getRawParameterValue("MIX")->load();
            
            // LFO
            auto lfoRate = mAPVTS.getRawParameterValue("LFORATE")->load();
            auto lfoDepth = mAPVTS.getRawParameterValue("LFODEPTH")->load();

            voice->updateAmpEnvelope (attack, decay, sustain, release);
            voice->updateChorus (rate, depth, centreDelay, feedback, mix);
            voice->updateLfo (lfoRate, lfoDepth);
        }
    }
    
    mEngineSampler.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool IbkSampledInstrumentAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* IbkSampledInstrumentAudioProcessor::createEditor()
{
    return new IbkSampledInstrumentAudioProcessorEditor (*this);
}

//==============================================================================
void IbkSampledInstrumentAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void IbkSampledInstrumentAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout IbkSampledInstrumentAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> rangedParameters;
    
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.0f, 5.0f, 0.0f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 0.0f, 5.0f, 2.5f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 0.8f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.0f, 10.0f, 7.0f));
    
    rangedParameters.push_back (std::make_unique<juce::AudioParameterInt>  ("RATE", "Rate", 0, 99, 4));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("DEPTH", "Depth", 0.0f, 1.0f, 0.25f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterInt>  ("CENTREDELAY", "Centre Delay", 1, 99, 1));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", -1.0f, 1.0f, 0.0f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 1.0f, 0.6f));
    
//    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("LFORATE", "LfoRate", 0.0f, 100000.0f, 20.0f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("LFORATE", "LfoRate", juce::NormalisableRange<float> { 0.0f, 10000.0f, 100.0f }, 0.0f, "Hz"));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("LFODEPTH", "LfoDepth", 0.0f, 1.0f, 0.6f));
    
    return { rangedParameters.begin(), rangedParameters.end()} ;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IbkSampledInstrumentAudioProcessor();
}
