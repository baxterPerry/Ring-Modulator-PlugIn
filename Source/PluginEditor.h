/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Processing1AudioProcessorEditor  : public AudioProcessorEditor

{
public:
    Processing1AudioProcessorEditor (Processing1AudioProcessor&, AudioProcessorValueTreeState& );
    ~Processing1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    Slider gainSlider;
    Slider freqSlider;
    Label freqSliderLabel;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Processing1AudioProcessor& processor;
    Image background;
    AudioProcessorValueTreeState& valueTreeState;
    
    //making an object of type <x> and naming it;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sFreqAttachment;

    Label gainSliderLabel;
    TextButton onOff;
    Label onOffLabel;

    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Processing1AudioProcessorEditor)
};
