/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Processing1AudioProcessor::Processing1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, Identifier("Ring Modulator"),
                    {
                        std::make_unique<AudioParameterFloat>("gain", //parameter ID
                                                             "Gain",// parameter name
                                                             0.1f,//min
                                                             1.0f, //max
                                                             0.5f //default value
                                                             ),
                        std::make_unique<AudioParameterFloat>("aFreq",
                                                              "aFreq",
                                                              1.0f,
                                                              20.0f,
                                                              5.0f)
                           
                    }
                                     
                                     )
#endif
{
    //Initialization
    gainParameter = parameters.getRawParameterValue("gain");
    freqParameter = parameters.getRawParameterValue("Freq");

}

Processing1AudioProcessor::~Processing1AudioProcessor()
{
}

//==============================================================================
const String Processing1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Processing1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Processing1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Processing1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Processing1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Processing1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Processing1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Processing1AudioProcessor::setCurrentProgram (int index)
{
}

const String Processing1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Processing1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

void Processing1AudioProcessor::updateAngleDelta()
{
    auto cyclesPerSample = *freqParameter / currentSampleRate; //= x/currentSampleRate ie 1000/currentSampleRate
    angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void Processing1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    //sinFreq.reset(sampleRate, 0.05f);
    //thruZero = false;
    updateAngleDelta();
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    level.reset(sampleRate, 0.05f);
    level.setTargetValue(0.5f);
    sFreq.reset(sampleRate, 0.05f);
    sFreq.setTargetValue(200.0f);
}



void Processing1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Processing1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Processing1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //clears all excess input channels


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
                
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            //float f = sinFreq.getNextValue();
            //const auto readPointer = buffer.getReadPointer(channel);
            level.getNextValue();
            sFreq.getNextValue();
            auto currentSample = (float) std::sin (currentAngle);
            currentAngle += angleDelta;            
            channelData[sample]  = channelData[sample] * currentSample * *gainParameter;
            
            //i have worked out i can control my level of the whole plugin with level
            //but i still cant hear any of the audiofile coming in *$%#$ >:[
        }

        // ..do something to the data...
        
    }
}

//==============================================================================
bool Processing1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Processing1AudioProcessor::createEditor()
{
    return new Processing1AudioProcessorEditor (*this, parameters);
}

//==============================================================================
void Processing1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    //GET CURRENT INFORMATION OF PLUGIN TO SAVE IT FOR FUTURE
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Processing1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //SAVING DATA TO THE PLUGIN
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
    {
        if (xmlState ->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(ValueTree::fromXml(*xmlState));
        }
    }
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processing1AudioProcessor();
}
