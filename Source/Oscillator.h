/*
  ==============================================================================

    Oscillator.h
    Created: 22 Mar 2020 4:28:45pm
    Author:  timmy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component
{
public:
    Oscillator(SynthFrameworkAudioProcessor&, AudioProcessorValueTreeState&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

    // In fact, as the names of these classes can become very long, we have included a typedef for each of the attachment classes we need:
    typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

private:
    SynthFrameworkAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    ComboBox oscMenu;
    std::unique_ptr<ComboBoxAttachment> waveSelection;   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
