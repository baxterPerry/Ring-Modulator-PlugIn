/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Processing1AudioProcessorEditor::Processing1AudioProcessorEditor (Processing1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    gainSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 20, 200);
    gainSlider.setRange(500.0f, 2500.0f, 3);
    gainSlider.setTextValueSuffix(" Hz");
    addAndMakeVisible(gainSlider);
    
    freqSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    freqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 20, 200);
    freqSlider.setRange(0.0f, 0.5f);
    freqSlider.setNumDecimalPlacesToDisplay(2);
    freqSlider.setTextValueSuffix("Gain");
    addAndMakeVisible(freqSlider);
    
    onOff.changeWidthToFitText(20);
    addAndMakeVisible(onOff);
    
    addAndMakeVisible(onOffLabel);


    


    //initialize variables
    //load assets ie background and stuff like that
}

Processing1AudioProcessorEditor::~Processing1AudioProcessorEditor()
{
    //memory management, what happens when plug in closes
    //irellevant atm
}

//==============================================================================
void Processing1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour(Colours::papayawhip);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 40);
    g.setColour(Colours::cornflowerblue);
    g.fillRect(0, 50, getWidth(), 10) ;
    g.setColour(Colours::sienna);
    g.fillRect(0, 100, getWidth(), 10) ;
    g.setColour(Colours::gainsboro);
    g.fillRect(0, 150, getWidth(), 10) ;
    g.setColour(Colours::sienna);
    g.fillRect(0, 200, getWidth(), 10) ;
    g.setColour(Colours::cornflowerblue);
    g.fillRect(0, 250, getWidth(), 10) ;
    g.setFont(Font::bold);
    g.setColour(Colours::whitesmoke);
    //g.drawText("bishyfkauldhjb", getWidth()/2, 1, 10, 100, 100);
    
}

void Processing1AudioProcessorEditor::resized()
{
    gainSlider.setBounds(80, 50, 50, 200);
    freqSlider.setBounds(270, 50, 50, 200);
    onOff.setBounds((getWidth()/2)-10, (getHeight()/2)-5, 500, 50);
    onOffLabel.setBounds((getWidth()/2)-10, (getHeight()/2), 20, 20);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
