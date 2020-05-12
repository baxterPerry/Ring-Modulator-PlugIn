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
class Processing1AudioProcessorEditor  : public AudioProcessorEditor,                                                                 private Slider::Listener

{
public:
    Processing1AudioProcessorEditor (Processing1AudioProcessor&);
    ~Processing1AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    Slider gainSlider;
    Slider freqSlider;
    Label freqSliderLabel;
    void sliderValueChanged (Slider* slider) override ;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Processing1AudioProcessor& processor;
    Image background;

    Label gainSliderLabel;
    TextButton onOff;
    Label onOffLabel;

    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Processing1AudioProcessorEditor)
};
