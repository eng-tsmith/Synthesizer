/*
  ==============================================================================

    Oscillator.cpp
    Created: 22 Mar 2020 4:28:45pm
    Author:  timmy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameworkAudioProcessor& p, AudioProcessorValueTreeState& vts) :
    processor(p), valueTreeState(vts)
{
    setSize(200, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&oscMenu);

    waveSelection.reset(new ComboBoxAttachment(valueTreeState, "wavetype", oscMenu));

}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscMenu.setBounds(area.removeFromTop(20));

}
