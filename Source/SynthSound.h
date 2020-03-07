/*
  ==============================================================================

    SynthSound.h
    Created: 24 Feb 2020 8:23:49pm
    Author:  timmy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }

    bool appliesToChannel(int /*midiNoteChannel*/)
    {
        return true;
    }

private:

};