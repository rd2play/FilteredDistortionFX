#include "pch.h"
#include "AudioFile.h"
#include "FilteredDistortion.h"

TEST(TestCaseName, TestFilteredDistortion) {
    //EXPECT_EQ(1, 1);
    //EXPECT_TRUE(true);
    constexpr auto testtrack =
        "C:/JUCEProjects/FilteredDistortion/Builds/UnitTest/wavTonescom_sin_1500Hz.wav";
    AudioFile<float>::AudioBuffer buffer;
    AudioFile<float> audioFile;
    audioFile.load(testtrack);    
    // ASSERT_EQ(audioFile.getNumChannels(), 1);

    auto bitDepth = audioFile.getBitDepth();
    auto numChannels = audioFile.getNumChannels();
    auto numSamplesPerChannel = audioFile.getNumSamplesPerChannel();
    auto sampleRate = audioFile.getSampleRate();

    buffer.resize(1);
    buffer[0].resize(numSamplesPerChannel);
    // buffer[1].resize(numSamplesPerChannel);

    FilteredDistortion::FilteredDistortion fdeffect;     
    //std::array<FilteredDistortion::FilteredDistortion, 1> fdeffect2;
    //for (auto& fd : fdeffect) {
    //fdeffect.sets.setSampleRate(sampleRate);
    //}
    fdeffect.setSampleRate(sampleRate);
    fdeffect.setGain1(7);
    fdeffect.setFrequency1(1500.0f);    
    fdeffect.setBandpass1Parameters();

    for (int i = 0; i < numSamplesPerChannel; i++) {        
        auto currentSample = audioFile.samples[0][i];

        // for (int channel = 0; channel < numChannels; channel++)
        //{
        float leftChannelData = fdeffect.processTest(currentSample, 1);
        buffer[0][i] = leftChannelData;
        //}
    }
    bool ok = audioFile.setAudioBuffer(buffer);

    // Set both the number of channels and number of samples per channel
    audioFile.setAudioBufferSize(numChannels, numSamplesPerChannel);

    // Set the number of samples per channel
    audioFile.setNumSamplesPerChannel(numSamplesPerChannel);

    // Set the number of channels
    audioFile.setNumChannels(numChannels);

    audioFile.setBitDepth(bitDepth);
    audioFile.setSampleRate(sampleRate);

    audioFile.save(
        "C:/JUCEProjects/FilteredDistortion/Builds/UnitTest/audioFile.wav",
        AudioFileFormat::Wave);
}