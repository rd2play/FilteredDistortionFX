/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FilteredDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FilteredDistortionAudioProcessorEditor (FilteredDistortionAudioProcessor&);
    ~FilteredDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider eq1slider;
    juce::Slider eq2slider;
    juce::Slider eq3slider;
    juce::Slider gain1slider;
    juce::Slider gain2slider;
    juce::Slider gain3slider;
    juce::ComboBox choice;
    juce::Slider gainAllslider;
    juce::Label gainAllLabel{"Gain Full"};
    juce::Label gain1Label{"Gain freq 1"};
    juce::Label gain2Label{"Gain freq 2"};
    juce::Label gain3Label{"Gain freq 3"};
    juce::Label freq1Label{"Frreq 1"};
    juce::Label freq2Label{"Frreq 2"};
    juce::Label freq3Label{"Frreq 3"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> eq1sliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> eq2sliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> eq3sliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gain1sliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gain2sliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gain3sliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> choiceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAllsliderAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilteredDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilteredDistortionAudioProcessorEditor)
};
