#pragma once
#include "Bandpass.h"
#include "FilteredDistortion.h"
#include "LFO.h"

namespace AutoWah {
class AutoWah {
 public:
  void process(float* samples, int samplesCount);
  void prepareToPlay(double sampleRate, int samplesPerBlock);  
  void setLFORate(float lforate) { _lfo.setFrequency(lforate); }
  void setFrequency(float freq) { cutoffFrequency = freq; }
  
 private:
  CF::LFO _lfo;
  FilteredDistortion::Bandpass bandpass; 
  void updateLFOBandpassParameters();
  float _sampleRate{0.f};
  float cutoffFrequency{0.f};
};
}  // namespace AutoWah
