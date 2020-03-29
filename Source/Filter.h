/*
  ==============================================================================

    Filter.h
    Created: 28 Mar 2020 1:27:14pm
    Author:  timmy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(SynthFrameworkAudioProcessor&, AudioProcessorValueTreeState&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

    // In fact, as the names of these classes can become very long, we have included a typedef for each of the attachment classes we need:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

private:
    SynthFrameworkAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    // Type
    ComboBox filterMenu;
    std::unique_ptr<ComboBoxAttachment> filterSelection;

    // Cut off
    Label cutOffLabel;
    Slider cutOffSlider;
    std::unique_ptr<SliderAttachment> cutOffAttachment;

    // Resonance
    Label resonanceLabel;
    Slider resonanceSlider;
    std::unique_ptr<SliderAttachment> resonanceAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
