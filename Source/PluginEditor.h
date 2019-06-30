/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class XViaAudioProcessorEditor  : public AudioProcessorEditor
{
public:
	
    XViaAudioProcessorEditor (XViaAudioProcessor&);
    ~XViaAudioProcessorEditor();
	
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;


private:

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sizev;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dampv;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> wetv;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryv;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> widthv;

	Slider sizeS;
	Slider dampS;
	Slider wetS;
	Slider dryS;
	Slider widthS;

    XViaAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XViaAudioProcessorEditor)
};

