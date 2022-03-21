/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DirectOSC.h"

//==============================================================================
/**
*/
class WillDirectOSCAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    WillDirectOSCAudioProcessor();
    ~WillDirectOSCAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void setFreq(float f)
    {
        osc1.setFreq(f);
    };
    void toggleOSC(bool t)
    {
        osc1.toggleOSC(t);
    };
    
    float getFreq()
    {
        return osc1.getFreq();
    };
    
    float getRunOSC()
    {
        return osc1.getRunOSC();
    };

private:
    
    float currentSampleRate;
    DirectOSC osc1;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WillDirectOSCAudioProcessor)
};
