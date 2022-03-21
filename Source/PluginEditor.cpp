/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WillDirectOSCAudioProcessorEditor::WillDirectOSCAudioProcessorEditor (WillDirectOSCAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(freqSlider);
    freqSlider.setNormalisableRange(juce::NormalisableRange<double>(20.f, 5000.f, 1.f, 1.f));
    freqSlider.addListener (this);
    freqSlider.setValue(audioProcessor.getFreq());
    addAndMakeVisible (freqLabel);
    freqLabel.setText ("osc frequency", juce::dontSendNotification);
    freqLabel.attachToComponent (&freqSlider, true);
    
    addAndMakeVisible (toggleButton);
    toggleButton.onClick = [this] { updateToggleState (&toggleButton, "toggleButton"); };
    toggleButton.setButtonText("on/off");
}

WillDirectOSCAudioProcessorEditor::~WillDirectOSCAudioProcessorEditor()
{
}

//==============================================================================
void WillDirectOSCAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void WillDirectOSCAudioProcessorEditor::resized()
{

    freqSlider.setBounds(100,150,250,20);
    toggleButton.setBounds(50,50,100,100);
}

void WillDirectOSCAudioProcessorEditor::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &freqSlider)
    {
        audioProcessor.setFreq(freqSlider.getValue());
    }
    
}

void WillDirectOSCAudioProcessorEditor::updateToggleState (juce::Button* button, juce::String name)
{
    if (name == "toggleButton")
    {
            audioProcessor.toggleOSC(!audioProcessor.getRunOSC());
    }
}
