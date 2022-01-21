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
                       ), mAPVTS (*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    mAPVTS.state.addListener (this);
    
    // Setup voices
    for (int i = 0; i < mNumVoices; i++)
    {
        mSampledInstrument.addVoice (new juce::SamplerVoice());
    }
    
    // Setup sampled sound
    mSampledInstrument.clearSounds();
    juce::WavAudioFormat wavFormat;
    
    std::unique_ptr<juce::AudioFormatReader> audioReader (wavFormat.createReaderFor (createSamplesInputStream ("os_synth.wav").release(), true));
    
    juce::BigInteger allNotes;
    allNotes.setRange (0, 128, true);
    
    mSampledInstrument.clearSounds();
    mSampledInstrument.addSound (new juce::SamplerSound ("vox",         // name
                                                         *audioReader,  // source
                                                         allNotes,      // midi notes range
                                                         74,            // root midi note
                                                         0.1,           // attack time (sec)
                                                         0.1,           // release time (sec)
                                                         30.0           // maximum sample length (sec)
                                                         ));
    
    updateEnvelopeValue();
    updateChorusValue();
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
    mSampledInstrument.setCurrentPlaybackSampleRate (sampleRate);
    
    // Chorus prepare
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = 2;
    
    mChorus.prepare (spec);
    mChorus.reset();
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
    
    mSampledInstrument.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<float> sampleBlock (buffer);
    mChorus.process (juce::dsp::ProcessContextReplacing<float> (sampleBlock));
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
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.0f, 10.0f, 3.0f));
    
    rangedParameters.push_back (std::make_unique<juce::AudioParameterInt>  ("RATE", "Rate", 0, 99, 4));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("DEPTH", "Depth", 0.0f, 1.0f, 0.25f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterInt>  ("CENTREDELAY", "Centre Delay", 1, 99, 1));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("FEEDBACK", "Feedback", -1.0f, 1.0f, 0.0f));
    rangedParameters.push_back (std::make_unique<juce::AudioParameterFloat>("MIX", "Mix", 0.0f, 1.0f, 0.6f));
    
    return { rangedParameters.begin(), rangedParameters.end()} ;
}

void IbkSampledInstrumentAudioProcessor::updateEnvelopeValue()
{
    mEnvelopeParameters.attack  = mAPVTS.getRawParameterValue ("ATTACK")->load();
    mEnvelopeParameters.decay   = mAPVTS.getRawParameterValue ("DECAY")->load();
    mEnvelopeParameters.sustain = mAPVTS.getRawParameterValue ("SUSTAIN")->load();
    mEnvelopeParameters.release = mAPVTS.getRawParameterValue ("RELEASE")->load();
    
    for (int i = 0; i < mSampledInstrument.getNumSounds(); i++)
    {
        if (auto sound = dynamic_cast<juce::SamplerSound*>(mSampledInstrument.getSound(i).get()))
        {
            sound->setEnvelopeParameters(mEnvelopeParameters);
        }
    }
}

void IbkSampledInstrumentAudioProcessor::updateChorusValue()
{
    mChorus.setRate(mAPVTS.getRawParameterValue("RATE")->load());
    mChorus.setDepth(mAPVTS.getRawParameterValue("DEPTH")->load());
    mChorus.setCentreDelay(mAPVTS.getRawParameterValue("CENTREDELAY")->load());
    mChorus.setFeedback(mAPVTS.getRawParameterValue("FEEDBACK")->load());
    mChorus.setMix(mAPVTS.getRawParameterValue("MIX")->load());
}

void IbkSampledInstrumentAudioProcessor::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{
    updateEnvelopeValue();
    updateChorusValue();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IbkSampledInstrumentAudioProcessor();
}
