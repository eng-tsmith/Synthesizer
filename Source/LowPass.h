/*
  ==============================================================================

    LowPass.h
    Created: 22 Mar 2020 7:28:46pm
    Author:  timmy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LowPass    : public Component
{
public:
    LowPass(SynthFrameworkAudioProcessor&, AudioProcessorValueTreeState&);
    ~LowPass();

    void paint (Graphics&) override;
    void resized() override;

    // In fact, as the names of these classes can become very long, we have included a typedef for each of the attachment classes we need:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

private:
    SynthFrameworkAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    Label cutOffLabel;
    Slider cutOffSlider;
    std::unique_ptr<SliderAttachment> cutOffAttachment;

    Label resonanceLabel;
    Slider resonanceSlider;
    std::unique_ptr<SliderAttachment> resonanceAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LowPass)
};
