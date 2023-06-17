#pragma once

namespace FilteredDistortion
{
    class Bandpass
    {
    public:
        float cutoffFrequency() const;
        void setCutoffFrequency(float digitalCutoffFrequency);
        void process(float* samples, int samplesCount);
        float process(float sample);

    private:
        float _cutoffFrequency;
        float b0{ 1.f }, b1{ 0.f }, b2{ 0.f }, a1{ 0.f }, a2{ 0.f }, a0{ 0.f };
        float s1{ 0.f }, s2{ 0.f };

    };

}
