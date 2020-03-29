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
    : AudioProcessorEditor (&p), valueTreeState(vts), oscGUI(p, vts), envGUI(p, vts), filterGUI(p, vts), lfoGUI(p, vts)
{
    setSize(800, 200);

    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(&lfoGUI);
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SynthFrameworkAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto r = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGUI.setBounds(r.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(r.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(r.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    lfoGUI.setBounds(r.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}
