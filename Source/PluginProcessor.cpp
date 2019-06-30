/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XViaAudioProcessor::XViaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	), parameters(*this, nullptr) // parameter value tree state
#endif
{

	NormalisableRange<float> sizeRange(0.0f, 100.0f, 1.0);
	NormalisableRange<float> dampRange(0.0f, 100.0f, 1.0);
	NormalisableRange<float> wetRange(0.0f, 100.0f, 1.0);
	NormalisableRange<float> dryRange(0.0f, 100.0f, 1.0);
	NormalisableRange<float> widthRange(0.0f, 100.0f, 1.0);

	// Dial parameters
	parameters.createAndAddParameter("size", "Size", "size", sizeRange, 10.0f, nullptr, nullptr);
	parameters.createAndAddParameter("damp", "Damp", "damp", dampRange, 40.0f, nullptr, nullptr);
	parameters.createAndAddParameter("wet", "Wet", "wet", wetRange, 50.0f, nullptr, nullptr);
	parameters.createAndAddParameter("dry", "Dry", "dry", dryRange, 35.0f, nullptr, nullptr);
	parameters.createAndAddParameter("width", "Width", "width", widthRange, 50.0f, nullptr, nullptr);

	// For saving parameter state
	parameters.state = ValueTree("savedParams");
}


XViaAudioProcessor::~XViaAudioProcessor()
{
}

//==============================================================================
const String XViaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool XViaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool XViaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool XViaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double XViaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int XViaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int XViaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void XViaAudioProcessor::setCurrentProgram (int index)
{
}

const String XViaAudioProcessor::getProgramName (int index)
{
    return {};
}

void XViaAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void XViaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	
	// Preparing Reverb
	revFx.setSampleRate(sampleRate);
	revFx.reset();

	// Calling update function to specify parameters
	updateEffect();


}

void XViaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void XViaAudioProcessor::updateEffect() {


	revFx.getParameters();

	// Getting dial parameter value
	float size = *parameters.getRawParameterValue("size");
	float damp = *parameters.getRawParameterValue("damp");
	float wet = *parameters.getRawParameterValue("wet");
	float dry = *parameters.getRawParameterValue("dry");
	float width = *parameters.getRawParameterValue("width");

	// Multiplying by 0.01 allows for the view of the parameters to be 0 - 100, while following the effects parameter bounds of 0.0 - 1.0
	float reducedAmt = 0.01;


		revP.roomSize = size * reducedAmt;
		revP.damping = damp * reducedAmt;
		revP.wetLevel = wet * reducedAmt;
		revP.dryLevel = dry * reducedAmt;
		revP.width = width * reducedAmt;

		revFx.setParameters(revP);

}


#ifndef JucePlugin_PreferredChannelConfigurations
bool XViaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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




void XViaAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	const auto numChannels = jmin(totalNumInputChannels, totalNumOutputChannels);
	
	// Calling update function to update parameters
	updateEffect();
		for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
			buffer.clear(i, 0, buffer.getNumSamples());


		// Checking if number of channels allows for mono only or stereo

		if (numChannels == 1) // Mono
			revFx.processMono(buffer.getWritePointer(0), buffer.getNumSamples());


		else if (numChannels == 2) // Stereo
			revFx.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());

	
	
	
	
	
 
}

//==============================================================================
bool XViaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* XViaAudioProcessor::createEditor()
{
    return new XViaAudioProcessorEditor (*this);
}

//==============================================================================
void XViaAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	ScopedPointer <XmlElement> xml(parameters.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void XViaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ScopedPointer <XmlElement> loadParams(getXmlFromBinary(data, sizeInBytes));

	if (loadParams != nullptr)
	{
		if (loadParams->hasTagName(parameters.state.getType()))
		{
			parameters.state = ValueTree::fromXml(*loadParams);

		}

	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new XViaAudioProcessor();
}
