#include "AutoWah.h"
#include <cmath>

namespace AutoWah {

    void AutoWah::process(float* samples, int samplesCount) {
        for (int i = 0; i < samplesCount; i++) {
            updateLFOBandpassParameters();
            const auto bandpassfilteredsample = bandpass.process(samples[i]);            
            samples[i] = samples[i] + (bandpassfilteredsample);
        }
    }

    void AutoWah::prepareToPlay(double sr, int samplesPerBlock) {
        _sampleRate = sr;
        _lfo.setFrequency(2.5f);
        _lfo.setSampleRate(_sampleRate);
        //setFrequency(2000.f);
        bandpass.setCutoffFrequency(2000.f / _sampleRate);
    }    
  
    void AutoWah::updateLFOBandpassParameters() {
        auto lfoValue = _lfo.getNextSample();
        // modulate unipolar for experimentation
        //lfoValue = (lfoValue + 1.f) / 2.f;
        bandpass.setCutoffFrequency((3500 + (3000.f * lfoValue)) /
                                    _sampleRate);
    }

}  // namespace AutoWah