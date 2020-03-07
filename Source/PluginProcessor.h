/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class SynthFrameworkAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SynthFrameworkAudioProcessor();
    ~SynthFrameworkAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;

    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //float attackTime;
    //float decayTime;
    //float sustainTime;
    //float releaseTime;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthFrameworkAudioProcessor)
    Synthesiser mySynth;
    SynthVoice* myVoice;
    double lastSampleRate;

    AudioProcessorValueTreeState parameters;
    std::atomic<float>* attackTimeParameter = nullptr;
    std::atomic<float>* decayTimeParameter = nullptr;
    std::atomic<float>* sustainTimeParameter = nullptr;
    std::atomic<float>* releaseTimeParameter = nullptr;

};