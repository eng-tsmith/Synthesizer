/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor (SynthFrameworkAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), 
    valueTreeState(vts)
{
    // Attack Slider
    attackLabel.setText("Attack", dontSendNotification);
    addAndMakeVisible(attackLabel);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 10);
    addAndMakeVisible(attackSlider);
    attackAttachment.reset(new SliderAttachment(valueTreeState, "attack", attackSlider));

    // Decay Slider
    decayLabel.setText("Decay", dontSendNotification);
    addAndMakeVisible(decayLabel);
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 10);
    addAndMakeVisible(decaySlider);
    decayAttachment.reset(new SliderAttachment(valueTreeState, "decay", decaySlider));

    // Sustain Slider
    sustainLabel.setText("Sustain", dontSendNotification);
    addAndMakeVisible(sustainLabel);
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 10);
    addAndMakeVisible(sustainSlider);
    sustainAttachment.reset(new SliderAttachment(valueTreeState, "sustain", sustainSlider));

    // Release Slider
    releaseLabel.setText("Release", dontSendNotification);
    addAndMakeVisible(releaseLabel);
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 10);
    addAndMakeVisible(releaseSlider);
    releaseAttachment.reset(new SliderAttachment(valueTreeState, "release", releaseSlider));

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(paramSliderWidth + paramLabelWidth, jmax(100, paramControlHeight * 5));
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // g.setColour (Colours::white);
    // g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void SynthFrameworkAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds();

    auto attackRect = r.removeFromTop(paramControlHeight);
    attackLabel.setBounds(attackRect.removeFromLeft(paramLabelWidth));
    attackSlider.setBounds(attackRect);

    auto decayRect = r.removeFromTop(paramControlHeight);
    decayLabel.setBounds(decayRect.removeFromLeft(paramLabelWidth));
    decaySlider.setBounds(decayRect);

    auto sustainRect = r.removeFromTop(paramControlHeight);
    sustainLabel.setBounds(sustainRect.removeFromLeft(paramLabelWidth));
    sustainSlider.setBounds(sustainRect);

    auto releaseRect = r.removeFromTop(paramControlHeight);
    releaseLabel.setBounds(releaseRect.removeFromLeft(paramLabelWidth));
    releaseSlider.setBounds(releaseRect);
}
