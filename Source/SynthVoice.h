/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Feb 2020 8:24:02pm
    Author:  timmy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Maximilian.h"


class SynthVoice : public SynthesiserVoice
{
public:

    //void initVoice()
    //{
    //    myZero.initZero();
    //}

    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    //==========================================

    void getParam (std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release, double frequency)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
        frequency_zmq = frequency;
    }

    void setFreqMQ(double freq)
    {
        frequency_zmq = freq;
    }
        

    //==========================================

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << midiNoteNumber << std::endl;
    }

    //==========================================

    void stopNote(float velocity, bool allowTailOff)
    {
        env1.trigger = 0; 
        allowTailOff = true;

        if (velocity == 0)
        {
            clearCurrentNote();
        }
    }

    //==========================================

    void pitchWheelMoved(int newPitchWheelValue)
    {

    }

    //==========================================

    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }

    //==========================================

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
       
        for (int sample = 0; sample < numSamples; ++sample)
        {
            // wave table
            double theWave = osc1.sinewave(frequency_zmq);  // myZero.recMsg()
            //env for my wavetable
            double theSound = env1.adsr(theWave, 1);// env1.trigger); //TODO *level;
            //filter
            double filteredSound = filter1.lores(theSound, 200, 0.1);


            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound);
            }
            ++startSample;
        }
    }

    //==========================================

private:
    double level;
    double frequency;
    double frequency_zmq;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    //ZeroReceiver myZero;

};
