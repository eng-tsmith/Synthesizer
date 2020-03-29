/*
  ==============================================================================

    Filter.cpp
    Created: 28 Mar 2020 1:27:14pm
    Author:  timmy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(SynthFrameworkAudioProcessor& p, AudioProcessorValueTreeState& vts) :
processor(p), valueTreeState(vts)
{
    setSize(200, 200);

    // filter type
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterSelection.reset(new ComboBoxAttachment(valueTreeState, "filtertype", filterMenu));

    // Cut off Slider
    cutOffLabel.setText("Cut off", dontSendNotification);
    addAndMakeVisible(cutOffLabel);
    cutOffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    cutOffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(cutOffSlider);
    cutOffAttachment.reset(new SliderAttachment(valueTreeState, "filtercutoff", cutOffSlider));
    cutOffSlider.setSkewFactorFromMidPoint(1000.0);

    // Resonance Slider
    resonanceLabel.setText("Resonance", dontSendNotification);
    addAndMakeVisible(resonanceLabel);
    resonanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    resonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(resonanceSlider);
    resonanceAttachment.reset(new SliderAttachment(valueTreeState, "filterresonance", resonanceSlider));
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Filter::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    filterMenu.setBounds(area.removeFromTop(20));

    auto cutOffRect = area.removeFromLeft(60);
    cutOffLabel.setBounds(cutOffRect.removeFromTop(20));
    cutOffSlider.setBounds(cutOffRect);

    auto resonanceRect = area.removeFromLeft(60);
    resonanceLabel.setBounds(resonanceRect.removeFromTop(20));
    resonanceSlider.setBounds(resonanceRect);
}
