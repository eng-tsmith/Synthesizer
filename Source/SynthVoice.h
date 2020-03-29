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

    void setOscType(std::atomic<float>* selection, std::atomic<float>* level1)
    {
        theWave = int(*selection);
        level_osc = double(*level1);
    }


    //==========================================

    void setFrequency(double frequency)
    {
        frequency_zmq = frequency;
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

    void setEnvel(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    }

    //==========================================

    double getEnvel()
    {
        return env1.adsr(getOscType(), 1);
    }

    //==========================================

    void setFilter(std::atomic<float>* selection, std::atomic<float>* cutoff1, std::atomic<float>* resonance1)
    {
        filterChoice = int(*selection);
        cutoff = double(*cutoff1);
        resonance = double(*resonance1);
    }

    //==========================================

    double getFilter()
    {
        if (filterChoice == 0)
        {
            return filter1.lores(getEnvel(), cutoff + (cutoff/2) * getLfo(), resonance);
        }
        else if (filterChoice == 1)
        {
            return filter1.hires(getEnvel(), cutoff + (cutoff / 2) *getLfo(), resonance);
        }
        else if (filterChoice == 2)
        {
            return filter1.bandpass(getEnvel(), cutoff + (cutoff / 2) * getLfo(), resonance);
        }
        else
        {
            DBG("ERROR FILTERTYPE");
            return filter1.lores(getEnvel(), cutoff + (cutoff / 2) * getLfo(), resonance);
        }
    }

    //==========================================

    void setLfo(std::atomic<float>* selection, std::atomic<float>* lforate1)
    {
        lfoChoice = int(*selection);
        lfoRate = double(*lforate1);
    }

    //==========================================

    double getLfo()
    {
        if (lfoChoice == 0)
        {
            return lfo1.sinewave(lfoRate);
        }
        else if (lfoChoice == 1)
        {
            return lfo1.square(lfoRate);
        }
        else if (lfoChoice == 2)
        {
            return lfo1.saw(lfoRate);
        }
        else
        {
            DBG("ERROR LFOTYPE");
            return lfo1.sinewave(lfoRate);
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
            // do audio stuff
            double current_sample = getFilter() * level_osc;

            // put on each channel
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, current_sample);
            }
            ++startSample;
        }
    }

    //==========================================

private:
    double level;
    double level_osc;
    double frequency;
    double frequency_zmq;
    //filter
    int filterChoice;
    double cutoff;
    double resonance;
    //osc
    int theWave;
    //lfo
    int lfoChoice;
    double lfoRate;

    maxiOsc osc1;
    maxiOsc lfo1;
    maxiEnv env1;
    maxiFilter filter1;
};
