/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Processing1AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Processing1AudioProcessor();
    ~Processing1AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void updateAngleDelta();
    

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    
    



private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Processing1AudioProcessor)
    AudioProcessorValueTreeState parameters;
    std::atomic<float>* gainParameter = nullptr;
    std::atomic<float>* freqParameter = nullptr;
    SmoothedValue<float> level;
    SmoothedValue<float> sFreq;
   
    //double level;
    double currentSampleRate = 0.0, currentAngle = 0.0, angleDelta = 0.0;

    
    //float gainSliderValue {0.1f};
    float sinFreq {1000.0};
    //float mGain {0.1};
};
