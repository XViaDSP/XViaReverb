/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#include <string>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XViaAudioProcessorEditor::XViaAudioProcessorEditor (XViaAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	//Set window size (Width, Height)
	setSize(370, 295);


	//Setting custom LookAndFeel
	getLookAndFeel().setColour(Slider::trackColourId, Colour::fromRGB(140, 180, 210));
	getLookAndFeel().setColour(Slider::backgroundColourId, Colour::fromRGB(0, 110, 130));
	getLookAndFeel().setColour(Slider::rotarySliderFillColourId, Colour::fromRGB(140, 180, 210));
	getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId, Colour::fromRGB(0, 110, 130));
	getLookAndFeel().setColour(Slider::thumbColourId, Colour::fromRGBA(153, 163, 203, 0));

	//Size Dial
	sizeS.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	sizeS.setRange(0.0f, 100.0f);
	sizeS.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	sizeS.setColour(Slider::textBoxOutlineColourId, Colour::fromRGB(32, 42, 62));
	sizeS.setColour(Slider::textBoxBackgroundColourId, Colour::fromRGB(32, 42, 62));
	sizeS.setPopupDisplayEnabled(false, false, this);
	sizeS.setTextValueSuffix("%");
	addAndMakeVisible(&sizeS);

	//Damp Dial
	dampS.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	dampS.setRange(0.0f, 100.0f);
	dampS.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	dampS.setPopupDisplayEnabled(false, false, this);
	dampS.setColour(Slider::textBoxOutlineColourId, Colour::fromRGB(32, 42, 62));
	dampS.setColour(Slider::textBoxBackgroundColourId, Colour::fromRGB(32, 42, 62));
	dampS.setTextValueSuffix("%");
	addAndMakeVisible(&dampS);

	//Width Dial
	widthS.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	widthS.setRange(0.0f, 100.0f);
	widthS.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	widthS.setColour(Slider::textBoxOutlineColourId, Colour::fromRGB(32, 42, 62));
	widthS.setColour(Slider::textBoxBackgroundColourId, Colour::fromRGB(32, 42, 62));
	widthS.setPopupDisplayEnabled(false, false, this);
	widthS.setTextValueSuffix("%");
	addAndMakeVisible(&widthS);

	//Dry Dial
	dryS.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	dryS.setRange(0.0f, 100.0f);
	dryS.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	dryS.setColour(Slider::textBoxOutlineColourId, Colour::fromRGB(52, 62, 82));
	dryS.setColour(Slider::textBoxBackgroundColourId, Colour::fromRGB(52, 62, 82));
	dryS.setPopupDisplayEnabled(false, false, this);
	dryS.setTextValueSuffix("%");
	addAndMakeVisible(&dryS);

	//Wet Dial
	wetS.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	wetS.setRange(0.0f, 100.0f);
	wetS.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
	wetS.setColour(Slider::textBoxOutlineColourId, Colour::fromRGB(52, 62, 82));
	wetS.setColour(Slider::textBoxBackgroundColourId, Colour::fromRGB(52, 62, 82));
	wetS.setPopupDisplayEnabled(false, false, this);
	wetS.setTextValueSuffix("%");
	addAndMakeVisible(&wetS);



	//Setting dial values to parameters

	sizev = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "size", sizeS);
	dampv = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "damp", dampS);
	widthv = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "width", widthS);
	dryv = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "dry", dryS);
	wetv = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "wet", wetS);


}

XViaAudioProcessorEditor::~XViaAudioProcessorEditor()
{
}

//==============================================================================
void XViaAudioProcessorEditor::paint (Graphics& g)
{

	//==========[Background]==========

	Rectangle<float> area(0, 0, 360, 300);
	g.fillAll(Colour::fromRGB(12, 22, 42));


	g.setColour(Colour::fromRGB(0, 110, 130));
	g.fillRoundedRectangle(5, 5, 360, 285, 20.0);

	g.setColour(Colour::fromRGB(32, 42, 62));
	g.fillRoundedRectangle(5, 145, 360, 145, 20.0);

	g.setColour(Colour::fromRGB(52, 62, 82));
	g.fillRoundedRectangle(5, 5, 360, 142, 20.0);

	g.setColour(Colour::fromRGB(0, 110, 130));
	g.drawRoundedRectangle(5, 5, 360, 285, 20.0, 3.0);

	g.setColour(Colour::fromRGB(32, 42, 62));
	g.fillRoundedRectangle(15, 15, 100, 125, 20.0);
	g.fillRoundedRectangle(135, 15, 100, 125, 20.0);
	g.fillRoundedRectangle(255, 15, 100, 125, 20.0);
	g.fillRoundedRectangle(15, 15, 300, 125, 20.0);

	g.setColour(Colour::fromRGB(52, 62, 82));
	g.fillRoundedRectangle(255, 155, 100, 125, 20.0);
	g.fillRoundedRectangle(15, 155, 100, 125, 20.0);
	g.fillRoundedRectangle(15, 155, 300, 125, 20.0);

	//================================

	//==========[Parameter Text]==========

	g.setColour (Colour::fromRGB(128, 200, 220));
	g.setFont(Font("Arial", 15.0f, 2));

	g.drawText("Size", 15, 55, 100, 20, Justification::centred);
	g.drawText("Damp", 135, 55, 100, 20, Justification::centred);
	g.drawText("Width", 255, 55, 100, 20, Justification::centred);
	g.drawText("Dry", 15, 195, 100, 20, Justification::centred);
	g.drawText("Wet", 255, 195, 100, 20, Justification::centred);

	//====================================

	//==========[Logo/Name Text]==========

	g.setFont(Font("Arial", 30.0f, 1));
	
	g.setColour(Colour::fromRGB(64, 140, 180));
	g.drawText("XVia", 110, 182, 150, 40, Justification::centred);
	g.drawText("Reverb", 110, 212, 150, 40, Justification::centred);

	g.setColour(Colour::fromRGB(0, 110, 130));
	g.drawText("XVia", 110, 178, 150, 40, Justification::centred);
	g.drawText("Reverb", 110, 208, 150, 40, Justification::centred);

	g.setColour(Colour::fromRGB(64, 140, 180));
	g.drawText("XVia", 108, 180, 150, 40, Justification::centred);
	g.drawText("Reverb", 108, 210, 150, 40, Justification::centred);

	g.setColour(Colour::fromRGB(0, 110, 130));
	g.drawText("XVia", 112, 180, 150, 40, Justification::centred);
	g.drawText("Reverb", 112, 210, 150, 40, Justification::centred);

	g.setColour(Colour::fromRGB(32, 42, 62));
	g.drawText("XVia", 110, 180, 150, 40, Justification::centred);
	g.drawText("Reverb", 110, 210, 150, 40, Justification::centred);

	//====================================

}

void XViaAudioProcessorEditor::resized()
{

	//Dial 'area'
	Rectangle<int> area = getLocalBounds();
	
	//Setting dial position and size
	sizeS.setBounds(15, 15, 100, 120);
	dampS.setBounds(135, 15, 100, 120);
	widthS.setBounds(255, 15, 100, 120);
	wetS.setBounds(255, 155, 100, 120);
	dryS.setBounds(15, 155, 100, 120);

}
