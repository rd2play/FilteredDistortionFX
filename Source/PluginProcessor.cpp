/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilteredDistortionAudioProcessor::FilteredDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
              ),
      apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

FilteredDistortionAudioProcessor::~FilteredDistortionAudioProcessor() {}

//==============================================================================
const juce::String FilteredDistortionAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool FilteredDistortionAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool FilteredDistortionAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool FilteredDistortionAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double FilteredDistortionAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int FilteredDistortionAudioProcessor::getNumPrograms() {
    return 1;  // NB: some hosts don't cope very well if you tell them there are
               // 0 programs, so this should be at least 1, even if you're not
               // really implementing programs.
}

int FilteredDistortionAudioProcessor::getCurrentProgram() {
    return 0;
}

void FilteredDistortionAudioProcessor::setCurrentProgram(int index) {}

const juce::String FilteredDistortionAudioProcessor::getProgramName(int index) {
    return {};
}

void FilteredDistortionAudioProcessor::changeProgramName(
    int index,
    const juce::String& newName) {}

//==============================================================================
void FilteredDistortionAudioProcessor::prepareToPlay(double sampleRate,
                                                     int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    // start block - uncomment for filtered distortion
    fdeffect[0].prepareToPlay(sampleRate, samplesPerBlock);
    fdeffect[1].prepareToPlay(sampleRate, samplesPerBlock);
    // end block

    // start block - uncomment for autowah
    // aweffect[0].prepareToPlay(sampleRate, samplesPerBlock);
    // aweffect[1].prepareToPlay(sampleRate, samplesPerBlock);
    // end block
}

void FilteredDistortionAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FilteredDistortionAudioProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void FilteredDistortionAudioProcessor::processBlock(
    juce::AudioBuffer<float>& buffer,
    juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto f1 = apvts.getRawParameterValue("FREQ1");
    auto f2 = apvts.getRawParameterValue("FREQ2");
    auto f3 = apvts.getRawParameterValue("FREQ3");
    auto g1 = apvts.getRawParameterValue("GAIN1");
    auto g2 = apvts.getRawParameterValue("GAIN2");
    auto g3 = apvts.getRawParameterValue("GAIN3");
    auto c1 = apvts.getRawParameterValue("CHOICE");
    auto gAll = apvts.getRawParameterValue("GAINALL");

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    // start block - uncomment for filtered distortion
    for (auto& fd : fdeffect) {
        fd.setAllBandsGain(*gAll);
        fd.setGain1(*g1);
        fd.setGain2(*g2);
        fd.setGain3(*g3);
        fd.setFrequency1(*f1);
        fd.setFrequency2(*f2);
        fd.setFrequency3(*f3);
        fd.setGainSelection(static_cast<int>(*c1));
    }
    // end block

    // start block - uncomment for autowah
    // for (auto& aw : aweffect) {
    //    aw.setFrequency(*f1);
    //}
    // end block

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(channel);

        // start block - uncomment for filtered distortion
        if (*c1 == 1) {
            fdeffect[channel].setBandpass1Parameters();
            fdeffect[channel].setBandpass2Parameters();
            fdeffect[channel].setBandpass3Parameters();
        }
        fdeffect[channel].process(channelData, buffer.getNumSamples());
        // end block

        // uncomment for autowah        
        // aweffect[channel].process(channelData, buffer.getNumSamples());
        // end block
    }
}

//==============================================================================
bool FilteredDistortionAudioProcessor::hasEditor() const {
    return true;  // (change this to false if you choose to not supply an
                  // editor)
}

juce::AudioProcessorEditor* FilteredDistortionAudioProcessor::createEditor() {
    return new FilteredDistortionAudioProcessorEditor(*this);
}

//==============================================================================
void FilteredDistortionAudioProcessor::getStateInformation(
    juce::MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FilteredDistortionAudioProcessor::setStateInformation(const void* data,
                                                           int sizeInBytes) {
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new FilteredDistortionAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout
FilteredDistortionAudioProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterInt>("FREQ1", "Freq1",
                                                               100, 900, 500));
    params.push_back(std::make_unique<juce::AudioParameterInt>(
        "FREQ2", "Freq2", 1000, 4000, 1500));
    params.push_back(std::make_unique<juce::AudioParameterInt>(
        "FREQ3", "Freq3", 4500, 7000, 5000));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "GAIN1", "Gain1", 1.f, 10.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "GAIN2", "Gain2", 1.f, 10.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "GAIN3", "Gain3", 1.f, 10.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        "CHOICE", "Choice", juce::StringArray("Full", "EQ based"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "GAINALL", "Gain", 1.f, 10.f, 1.f));

    return {params.begin(), params.end()};
}
