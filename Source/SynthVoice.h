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

    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    //==========================================

    void setEnvel(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    }

    //==========================================

    void setFrequency(double frequency)
    {
        frequency_zmq = frequency;
    }

    //==========================================

    void setOscType(std::atomic<float>* selection)
    {
        theWave = *selection;
    }

    //==========================================

    double getOscType()
    {
        if (theWave == 0)
        {
            return osc1.sinewave(frequency_zmq);
        }
        else if (theWave == 1)
        {
            return osc1.saw(frequency_zmq);
        }
        else if (theWave == 2)
        {
            return osc1.square(frequency_zmq);
        }
        else
        {
            DBG("ERROR WAVEFORM");
            return osc1.sinewave(440.0f);
        }
    }

    //==========================================

    void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        DBG(midiNoteNumber);
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
            //env for my wavetable
            double theSound = env1.adsr(getOscType(), 1); // env1.trigger); //TODO *level;
            //filter
           // TODO double filteredSound = filter1.lores(theSound, 200, 0.1);


            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, theSound);
            }
            ++startSample;
        }
    }

    //==========================================

private:
    double level;
    double frequency;
    double frequency_zmq;
    int theWave;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};
