/*
  ==============================================================================

    Lfo.cpp
    Created: 29 Mar 2020 11:20:21am
    Author:  timmy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Lfo.h"

//==============================================================================
Lfo::Lfo(SynthFrameworkAudioProcessor& p, AudioProcessorValueTreeState& vts) :
    processor(p), valueTreeState(vts)
{
    setSize(200, 200);

    // filter type
    lfomenu.addItem("Sine", 1);
    lfomenu.addItem("Square", 2);
    lfomenu.addItem("Saw", 3);
    lfomenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&lfomenu);
    lfoSelection.reset(new ComboBoxAttachment(valueTreeState, "lfotype", lfomenu));

    // Cut off Slider
    lfoLabel.setText("LFO rate", dontSendNotification);
    addAndMakeVisible(lfoLabel);
    lfoSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    lfoSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(lfoSlider);
    lfoSliderAttachment.reset(new SliderAttachment(valueTreeState, "lforate", lfoSlider));
    //cutOffSlider.setSkewFactorFromMidPoint(1000.0); // TODO 

}

Lfo::~Lfo()
{
}

void Lfo::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Lfo::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    lfomenu.setBounds(area.removeFromTop(20));

    auto lfoRect = area.removeFromLeft(60);
    lfoLabel.setBounds(lfoRect.removeFromTop(20));
    lfoSlider.setBounds(lfoRect);

}
