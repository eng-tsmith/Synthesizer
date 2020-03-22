/*
  ==============================================================================

    Envelope.h
    Created: 22 Mar 2020 6:34:54pm
    Author:  timmy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope();
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
