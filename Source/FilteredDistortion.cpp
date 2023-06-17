#include "FilteredDistortion.h"
#include <cmath>

namespace FilteredDistortion {

    double sgn(float v);
    float calculateSaturation(float bandpassfilteredsample, float gain);

    void FilteredDistortion::process(float* samples, int samplesCount) {
        for (int i = 0; i < samplesCount; i++) {
            if (gainSelection == 1) {
                const auto bandpass1filteredsample =
                    bandpass1.process(samples[i]);
                const auto f1 =
                    calculateSaturation(bandpass1filteredsample, gain1);

                const auto bandpass2filteredsample =
                    bandpass2.process(samples[i]);
                const auto f2 =
                    calculateSaturation(bandpass2filteredsample, gain2);

                const auto bandpass3filteredsample =
                    bandpass3.process(samples[i]);
                const auto f3 =
                    calculateSaturation(bandpass3filteredsample, gain3);

                samples[i] = f1 + f2 + f3 + samples[i] -
                             bandpass1filteredsample - bandpass2filteredsample -
                             bandpass3filteredsample;
            } else {
                const auto saturatedSample =
                    calculateSaturation(samples[i], gainAll);
                samples[i] = saturatedSample;
            }
        }
    }

    void FilteredDistortion::prepareToPlay(double sr, int samplesPerBlock) {
        sampleRate = sr;
        float digitalCutoffFrequency = 800 / sampleRate;
        bandpass1.setCutoffFrequency(digitalCutoffFrequency);
        digitalCutoffFrequency = 1500 / sampleRate;
        bandpass2.setCutoffFrequency(digitalCutoffFrequency);
        digitalCutoffFrequency = 5000 / sampleRate;
        bandpass3.setCutoffFrequency(digitalCutoffFrequency);
    }

    void FilteredDistortion::setBandpass1Parameters() {
        bandpass1.setCutoffFrequency(freq1 / sampleRate);
    }

    void FilteredDistortion::setBandpass2Parameters() {
        bandpass2.setCutoffFrequency(freq2 / sampleRate);
    }

    void FilteredDistortion::setBandpass3Parameters() {
        bandpass3.setCutoffFrequency(freq3 / sampleRate);
    }

    float calculateSaturation(float bandpassfilteredsample, float gain) {
        auto f = tanh(gain * bandpassfilteredsample) / tanh(gain);
        // now do some soft clipping
        f = sgn(f) * (1.0 - exp(-fabs(gain * f)));

        f = atan(gain * f) / atan(gain);
        f = f / gain;

        return f;
    }

    double sgn(float v) {
        return (v > 0) - (v < 0);
    }

    float FilteredDistortion::processTest(float samples, int samplesCount) {
        for (int i = 0; i < samplesCount; i++) {
            const auto bandpass1filteredsample = bandpass1.process(samples);
            const auto f1 = calculateSaturation(bandpass1filteredsample, gain1);

            samples = f1 + samples - bandpass1filteredsample;
        }
        return samples;
    }

}  // namespace FilteredDistortion