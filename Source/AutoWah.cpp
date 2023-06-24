#include "AutoWah.h"
#include <cmath>

namespace AutoWah {

    void AutoWah::process(float* samples, int samplesCount) {
        for (int i = 0; i < samplesCount; i++) {
            const auto bandpassfilteredsample = bandpass.process(samples[i]);            
            samples[i] = samples[i] + (bandpassfilteredsample);
        }
    }

    void AutoWah::prepareToPlay(double sr, int samplesPerBlock) {
        _sampleRate = sr;
        _lfo.setFrequency(500.f);
        _lfo.setSampleRate(_sampleRate);
        setFrequency(2000.f);
        bandpass.setCutoffFrequency(cutoffFrequency / _sampleRate);
    }    
  
    void AutoWah::updateLFOBandpassParameters() {
        auto lfoValue = _lfo.getNextSample();
        lfoValue = (lfoValue + 1.f) / 2.f;
        bandpass.setCutoffFrequency(
            (cutoffFrequency + (2000.f * lfoValue)) / _sampleRate);
    }

}  // namespace AutoWah