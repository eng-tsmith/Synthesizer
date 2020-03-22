/*
  ==============================================================================

    LowPass.cpp
    Created: 22 Mar 2020 7:28:46pm
    Author:  timmy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LowPass.h"

//==============================================================================
LowPass::LowPass(SynthFrameworkAudioProcessor& p, AudioProcessorValueTreeState& vts) :
    processor(p), valueTreeState(vts)
{
    setSize(200, 200);

    // Cut off Slider
    cutOffLabel.setText("Cut off", dontSendNotification);
    addAndMakeVisible(cutOffLabel);
    cutOffSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    cutOffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(cutOffSlider);
    cutOffAttachment.reset(new SliderAttachment(valueTreeState, "cutoff", cutOffSlider));

    // Resonance Slider
    resonanceLabel.setText("Resonance", dontSendNotification);
    addAndMakeVisible(resonanceLabel);
    resonanceSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    resonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(resonanceSlider);
    resonanceAttachment.reset(new SliderAttachment(valueTreeState, "resonance", resonanceSlider));
}

LowPass::~LowPass()
{
}

void LowPass::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void LowPass::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    auto cutOffRect = area.removeFromLeft(60);
    cutOffLabel.setBounds(cutOffRect.removeFromTop(20));
    cutOffSlider.setBounds(cutOffRect);

    auto resonanceRect = area.removeFromLeft(60);
    resonanceLabel.setBounds(resonanceRect.removeFromTop(20));
    resonanceSlider.setBounds(resonanceRect);
}
