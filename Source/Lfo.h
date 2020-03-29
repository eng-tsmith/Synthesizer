/*
  ==============================================================================

    Lfo.h
    Created: 29 Mar 2020 11:20:21am
    Author:  timmy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Lfo    : public Component
{
public:
    Lfo(SynthFrameworkAudioProcessor&, AudioProcessorValueTreeState&);
    ~Lfo();

    void paint (Graphics&) override;
    void resized() override;

    // In fact, as the names of these classes can become very long, we have included a typedef for each of the attachment classes we need:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

private:
    SynthFrameworkAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    // Type
    ComboBox lfomenu;
    std::unique_ptr<ComboBoxAttachment> lfoSelection;

    // lfo freq
    Label lfoLabel;
    Slider lfoSlider;
    std::unique_ptr<SliderAttachment> lfoSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lfo)
};
