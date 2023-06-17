#pragma once

namespace CF {
class LFO {
 public:
  float getNextSample();
  void setSampleRate(float sampleRate);
  void setFrequency(float frequency);

 private:
  float _phase{0.f};
  float _phaseIncrement{0.f};
  float _sampleRate{0.f};
};

}  
