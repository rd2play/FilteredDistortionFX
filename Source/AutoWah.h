#pragma once
#include "Bandpass.h"
#include "FilteredDistortion.h"
#include "LFO.h"

namespace AutoWah {
class AutoWah {
 public:
  void process(float* samples, int samplesCount);
  void prepareToPlay(double sampleRate, int samplesPerBlock);
  void setBandpassParameters();
  void setLFORate(float lforate) { _lfo.setFrequency(lforate); }
  void setFrequency(float freq) { digitalCutoffFrequency = freq; }
  
 private:
  CF::LFO _lfo;
  FilteredDistortion::Bandpass bandpass;  
  float _sampleRate{0.f};
  float digitalCutoffFrequency{0.f};
};
}  // namespace AutoWah
