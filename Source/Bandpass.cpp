#include "Bandpass.h"
#include <cmath>
#include <numbers>

namespace FilteredDistortion {

    float Bandpass::cutoffFrequency() const {
        return _cutoffFrequency;
    }

    void Bandpass::setCutoffFrequency(float digitalCutoffFrequency) {
        _cutoffFrequency = digitalCutoffFrequency;

        const auto Q = 8.7f;
        const auto pi = std::numbers::pi_v<float>;
        const auto omega = 2 * pi * digitalCutoffFrequency;
        const auto alpha = std::sin(omega) / (2 * Q);

        b0 = alpha;
        b1 = 0;
        b2 = -alpha;
        a0 = 1 + alpha;
        a1 = -2 * std::cos(omega);
        a2 = 1 - alpha;
    }

    void Bandpass::process(float* samples, int samplesCount) {
        for (int i = 0; i < samplesCount; i++) {
            const auto x = samples[i];
            const auto y = (b0 / a0) * x + s1;
            s1 = (b1 / a0) * x - (a1 / a0) * y + s2;
            s2 = (b2 / a0) * x - (a2 / a0) * y;

            const auto f = tanh(10.f * y);

            samples[i] = f;
        }
    }

    float Bandpass::process(float sample) {
        const auto x = sample;
        const auto y = (b0 / a0) * x + s1;
        s1 = (b1 / a0) * x - (a1 / a0) * y + s2;
        s2 = (b2 / a0) * x - (a2 / a0) * y;

        return y;
    }

}  // namespace FilteredDistortion