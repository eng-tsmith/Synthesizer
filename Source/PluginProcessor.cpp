/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "zmq_addon.hpp"
#include "ZeroReceiver.h"

//==============================================================================
SynthFrameworkAudioProcessor::SynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
#endif
parameters(*this, nullptr, Identifier("MyNiceSynth"),
        {
            std::make_unique<AudioParameterFloat>("attack",      // parameterID
                                                "Attack",        // parameter name
                                                1.0f,            // minimum value
                                                5000.0f,         // maximum value
                                                1.0f),           // default value
            std::make_unique<AudioParameterFloat>("decay",       // parameterID
                                                "Decay",         // parameter name
                                                1.0f,            // minimum value
                                                5000.0f,         // maximum value
                                                1.0f),           // default value
            std::make_unique<AudioParameterFloat>("sustain",     // parameterID
                                                "Sustain",       // parameter name
                                                1.0f,            // minimum value
                                                5000.0f,         // maximum value
                                                1.0f),           // default value
            std::make_unique<AudioParameterFloat>("release",     // parameterID
                                                "Release",       // parameter name
                                                1.0f,            // minimum value
                                                5000.0f,         // maximum value
                                                1.0f),           // default value
            std::make_unique<AudioParameterFloat>("wavetype",
                                                  "WaveType",
                                                   0,
                                                   2,
                                                   0),
            std::make_unique<AudioParameterFloat>("levelosc",
                                                  "LevelOSC",
                                                   0,
                                                   1,
                                                   0.8),
            std::make_unique<AudioParameterFloat>("filtertype",
                                                  "FilterType",
                                                   0,
                                                   2,
                                                   0),
            std::make_unique<AudioParameterFloat>("filtercutoff",
                                                  "FilterCutOff",
                                                   20,
                                                   5000,
                                                   1000),
            std::make_unique<AudioParameterFloat>("filterresonance",
                                                  "FilterResonance",
                                                   1,
                                                   5,
                                                   1),
            std::make_unique<AudioParameterFloat>("lfotype",
                                                  "LFOType",
                                                   0,
                                                   2,
                                                   0),
            std::make_unique<AudioParameterFloat>("lforate",
                                                  "LFORate",
                                                   1,
                                                   200,
                                                   5),
        })
{
    // init Voices
    mySynth.clearVoices();

    // Init ZeroMQ
    myZero.initZero();
    
    for (int i=0; i<5; i++)
    {
        auto voice = new SynthVoice();
        //voice->initVoice();
        mySynth.addVoice(voice);
    }

    // init Sounds
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

    // init params
    // env
    attackTimeParameter = parameters.getRawParameterValue("attack");
    decayTimeParameter = parameters.getRawParameterValue("decay");
    sustainTimeParameter = parameters.getRawParameterValue("sustain");
    releaseTimeParameter = parameters.getRawParameterValue("release");
    // osc
    waveTypeParameter = parameters.getRawParameterValue("wavetype");
    levelOSCParameter = parameters.getRawParameterValue("levelosc");
    // filter
    filterTypeParameter = parameters.getRawParameterValue("filterType");
    cutOffParameter = parameters.getRawParameterValue("filtercutoff");
    resonanceParameter = parameters.getRawParameterValue("filterresonance");
    // lfo
    lfoTypeParameter = parameters.getRawParameterValue("lfotype");;
    lfoRateParameter = parameters.getRawParameterValue("lforate");;

}

SynthFrameworkAudioProcessor::~SynthFrameworkAudioProcessor()
{
}

//==============================================================================
const String SynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFrameworkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthFrameworkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFrameworkAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthFrameworkAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthFrameworkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SynthFrameworkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    /*// init freq  TODO is this bug fix? init hipass seems to fix it?
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {          
            myVoice->setOscType(parameters.getRawParameterValue("wavetype"));
            myVoice->setFrequency(0.0);

            myVoice->setEnvel(parameters.getRawParameterValue("attack"),
                            parameters.getRawParameterValue("decay"),
                            parameters.getRawParameterValue("sustain"),
                            parameters.getRawParameterValue("release"));
            myVoice->setFilter(parameters.getRawParameterValue("filtertype"),
                               parameters.getRawParameterValue("filtercutoff"),
                               parameters.getRawParameterValue("filterresonance"));
        }
    }*/
}

void SynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFrameworkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SynthFrameworkAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    // read tree params and send to myVoice
    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->setOscType(parameters.getRawParameterValue("wavetype"),
                                parameters.getRawParameterValue("levelosc"));
            myVoice->setFrequency(myZero.recMsg());

            myVoice->setEnvel(parameters.getRawParameterValue("attack"), 
                              parameters.getRawParameterValue("decay"), 
                              parameters.getRawParameterValue("sustain"), 
                              parameters.getRawParameterValue("release"));                  
            myVoice->setFilter(parameters.getRawParameterValue("filtertype"),
                               parameters.getRawParameterValue("filtercutoff"),
                               parameters.getRawParameterValue("filterresonance"));
            myVoice->setLfo(parameters.getRawParameterValue("lfotype"),
                            parameters.getRawParameterValue("lforate"));
        }
    }

    buffer.clear();

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthFrameworkAudioProcessor::createEditor()
{
    //return new SynthFrameworkAudioProcessorEditor(*this);
    return new SynthFrameworkAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void SynthFrameworkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthFrameworkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFrameworkAudioProcessor();
}
