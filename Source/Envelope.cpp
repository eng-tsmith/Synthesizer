/*
  ==============================================================================

    Envelope.cpp
    Created: 22 Mar 2020 6:34:54pm
    Author:  timmy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p, AudioProcessorValueTreeState& vts) :
    processor(p), valueTreeState(vts)
{
    setSize(200, 200);

    // Attack Slider
    attackLabel.setText("A", dontSendNotification);
    addAndMakeVisible(attackLabel);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(attackSlider);
    attackAttachment.reset(new SliderAttachment(valueTreeState, "attack", attackSlider));

    // Decay Slider
    decayLabel.setText("D", dontSendNotification);
    addAndMakeVisible(decayLabel);
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(decaySlider);
    decayAttachment.reset(new SliderAttachment(valueTreeState, "decay", decaySlider));

    // Sustain Slider
    sustainLabel.setText("S", dontSendNotification);
    addAndMakeVisible(sustainLabel);
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(sustainSlider);
    sustainAttachment.reset(new SliderAttachment(valueTreeState, "sustain", sustainSlider));

    // Release Slider
    releaseLabel.setText("R", dontSendNotification);
    addAndMakeVisible(releaseLabel);
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(releaseSlider);
    releaseAttachment.reset(new SliderAttachment(valueTreeState, "release", releaseSlider));

}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    int rectWidth = 30;
    int labelHeight = 20;

    auto attackRect = area.removeFromLeft(rectWidth);
    attackLabel.setBounds(attackRect.removeFromTop(labelHeight));
    attackSlider.setBounds(attackRect);

    auto decayRect = area.removeFromLeft(rectWidth);
    decayLabel.setBounds(decayRect.removeFromTop(labelHeight));
    decaySlider.setBounds(decayRect);

    auto sustainRect = area.removeFromLeft(rectWidth);
    sustainLabel.setBounds(sustainRect.removeFromTop(labelHeight));
    sustainSlider.setBounds(sustainRect);

    auto releaseRect = area.removeFromLeft(rectWidth);
    releaseLabel.setBounds(releaseRect.removeFromTop(labelHeight));
    releaseSlider.setBounds(releaseRect);

}
