/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilteredDistortionAudioProcessorEditor::FilteredDistortionAudioProcessorEditor(FilteredDistortionAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    eq1slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    eq1slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(eq1slider);
    freq1Label.setText("Freq 1", juce::dontSendNotification);
    freq1Label.attachToComponent(&eq1slider, false);
    eq1sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ1", eq1slider);

    eq2slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    eq2slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(eq2slider);
    freq2Label.setText("Freq 2", juce::dontSendNotification);
    freq2Label.attachToComponent(&eq2slider, false);
    eq2sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ2", eq2slider);

    eq3slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    eq3slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(eq3slider);
    freq3Label.setText("Freq 3", juce::dontSendNotification);
    freq3Label.attachToComponent(&eq3slider, false);
    eq3sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "FREQ3", eq3slider);

    gain1slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gain1slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(gain1slider);
    gain1Label.setText("Gain Freq 1", juce::dontSendNotification);
    gain1Label.attachToComponent(&gain1slider, false);
    gain1sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN1", gain1slider);

    gain2slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gain2slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(gain2slider);
    gain2Label.setText("Gain Freq 2", juce::dontSendNotification);
    gain2Label.attachToComponent(&gain2slider, false);
    gain2sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN2", gain2slider);

    gain3slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gain3slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(gain3slider);
    gain3Label.setText("Gain Freq 3", juce::dontSendNotification);
    gain3Label.attachToComponent(&gain3slider, false);
    gain3sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN3", gain3slider);

    choice.addSectionHeading("Gain selection");    
    addAndMakeVisible(choice);
    choice.addItem("Full", 1);
    choice.addItem("EQ based", 2);
    choice.setSelectedId(1, juce::dontSendNotification);
    choiceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "CHOICE", choice);

    gainAllslider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainAllslider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(gainAllslider);
    gainAllLabel.setText("Gain Full", juce::dontSendNotification);
    gainAllLabel.attachToComponent(&gainAllslider, false);
    gainAllsliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAINALL", gainAllslider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 400);
}

FilteredDistortionAudioProcessorEditor::~FilteredDistortionAudioProcessorEditor()
{
}

//==============================================================================
void FilteredDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Filtered Distortion", getLocalBounds(), juce::Justification::centredTop, 1);
}

void FilteredDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    eq1slider.setBounds(getWidth() / 2 - 200, getHeight() / 2 - 100, 200,100);
    eq2slider.setBounds(getWidth() / 2, getHeight() / 2 - 100, 200, 100);
    eq3slider.setBounds(getWidth() / 2 + 200, getHeight() / 2 - 100, 200, 100);
    gain1slider.setBounds(getWidth() / 2 - 200, getHeight() / 2 + 50, 200, 100);
    gain2slider.setBounds(getWidth() / 2, getHeight() / 2 + 50, 200, 100);
    gain3slider.setBounds(getWidth() / 2 + 200, getHeight() / 2 + 50, 200, 100);
    choice.setBounds(getWidth() / 2 - 375, getHeight() / 2 - 150, 80, 40);
    gainAllslider.setBounds(getWidth() / 2 - 375, getHeight() / 2 + 50, 100, 100);

}
